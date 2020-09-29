#include "stdio.h"
#include <vector>
#include "vgl.h"
#include "objloader.h"
#include "utils.h"
#include "vmath.h"
#define DEG2RAD (M_PI/180.0)

using namespace vmath;
using namespace std;

enum VAO_IDs {Cube, Sphere, NumVAOs};
enum Buffer_IDs {CubePosBuffer, CubeColBuffer, CubeIndexBuffer, SpherePosBuffer, NumBuffers};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

GLint sphereVertices = 0;
GLint meshPosCoords = 4;
GLint cubePosCoords = 3;
GLint cubeColCoords = 4;
GLint cubeIndices = 36;
vec4 sphere_color = {1.0f, 1.0f, 0.0f, 1.0f};

// Declare projection matrix
mat4 proj_matrix = mat4().identity();
mat4 camera_matrix = mat4().identity();

// Camera
vec3 eye = {3.0f, 3.0f, 0.0f};
vec3 center = {0.0f, 0.0f, 0.0f};
vec3 up = {0.0f, 1.0f, 0.0f};

// Shader variables
GLuint mesh_program;
GLuint mesh_vPos;
GLuint mesh_vCol;
GLuint mesh_model_mat_loc;
GLuint mesh_proj_mat_loc;
GLuint mesh_cam_mat_loc;
GLuint grad_program;
GLuint grad_vPos;
GLuint grad_vCol;
GLuint grad_model_mat_loc;
GLuint grad_proj_mat_loc;
GLuint grad_cam_mat_loc;
const char *vertex_shader = "../color_grad.vert";
const char *mesh_shader = "../color_mesh.vert";
const char *frag_shader = "../color.frag";
const char *model = "../models/sphere.obj";

// Global state
GLfloat cube_angle = 0.0;
GLdouble elTime = 0.0;
GLdouble rpm = 10.0;
vec3 axis = {1.0f, 1.0f, 1.0f};

// Global spherical coord values
GLfloat azimuth = 0.0f;
GLfloat daz = 2.0f;
GLfloat elevation = 90.0f;
GLfloat del = 2.0f;
GLfloat radius = 6.0f;
GLfloat dr = 0.1f;
GLfloat min_radius = 2.0f;

// Global screen dimensions
GLint ww,hh;

void build_geometry( );
void display( );
void render_scene( );
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, int button, int action, int mods);
void draw_obj(GLuint VAO, GLuint Buffer, int numVert);

int main(int argc, char**argv)
{
	// Create OpenGL window
	GLFWwindow* window = CreateWindow("Shader Scene");
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    } else {
        printf("OpenGL window successfully created\n");
    }

    // Store initial window size in global variables
    glfwGetFramebufferSize(window, &ww, &hh);

    // Register callbacks
    glfwSetKeyCallback(window,key_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Get initial time
    elTime = glfwGetTime();

    // Create geometry buffers
    build_geometry();
    
    // Load shaders and associate variables
    // TODO: Mesh shader (uniform color)
	ShaderInfo mesh_shaders[] = { {GL_VERTEX_SHADER, mesh_shader},{GL_FRAGMENT_SHADER, frag_shader},{GL_NONE, NULL} };
    mesh_program = LoadShaders(mesh_shaders);
    mesh_vPos = glGetAttribLocation(mesh_program, "vPosition");
    mesh_vCol = glGetUniformLocation(mesh_program, "vColor");
    mesh_model_mat_loc = glGetUniformLocation(mesh_program, "model_matrix");
    mesh_proj_mat_loc = glGetUniformLocation(mesh_program, "proj_matrix");
    mesh_cam_mat_loc = glGetUniformLocation(mesh_program, "camera_matrix");

    // TODO: Gradient shader (per vertex color)
    ShaderInfo grad_shaders[] = { {GL_VERTEX_SHADER, vertex_shader},{GL_FRAGMENT_SHADER, frag_shader},{GL_NONE, NULL} };
    grad_program = LoadShaders(grad_shaders);
    grad_vPos = glGetAttribLocation(grad_program, "vPosition");
    grad_vCol = glGetAttribLocation(grad_program, "vColor");
    grad_model_mat_loc = glGetUniformLocation(grad_program, "model_matrix");
    grad_proj_mat_loc = glGetUniformLocation(grad_program, "proj_matrix");
    grad_cam_mat_loc = glGetUniformLocation(grad_program, "camera_matrix");

    // Enable depth test
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // Set initial camera position
    GLfloat x, y, z;
    x = (GLfloat)(radius*sin(azimuth*DEG2RAD)*sin(elevation*DEG2RAD));
    y = (GLfloat)(radius*cos(elevation*DEG2RAD));
    z = (GLfloat)(radius*cos(azimuth*DEG2RAD)*sin(elevation*DEG2RAD));
    eye = vec3(x, y, z);

    // Start loop
    while ( !glfwWindowShouldClose( window ) ) {
    	// Draw graphics
        display();
        // Update other events like input handling
        glfwPollEvents();
        // Update angle based on time for fixed rpm
        GLdouble curTime = glfwGetTime();
        //cube_angle += (curTime-elTime)*(rpm/60.0)*360.0;
        elTime = curTime;
        // Swap buffer onto screen
        glfwSwapBuffers( window );
    }

    // Close window
    glfwTerminate();
    return 0;
}

void build_geometry( )
{
    // Generate vertex arrays and buffers
	glGenVertexArrays(NumVAOs, VAOs);
    glGenBuffers(NumBuffers, Buffers);

    // Bind Cube vertex array object
	glBindVertexArray(VAOs[Cube]);

    // Define cube vertices
	GLfloat vertices[][3] = {
		{-1.0f, -1.0f, -1.0f},
        {1.0f, -1.0f, -1.0f},
        {1.0f, -1.0f, 1.0f},
        {-1.0f, -1.0f, 1.0f},
        {-1.0f, 1.0f, -1.0f},
        {1.0f, 1.0f, -1.0f},
        {1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f, 1.0f}
	};

	// Define cube colors (per vertex)
	GLfloat colors[][4] = {
		{0.0f, 0.0f, 0.0f, 1.0f},
		{1.0f, 0.0f, 0.0f, 1.0f},
		{1.0f, 0.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 0.0f, 1.0f},
		{1.0f, 1.0f, 0.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f, 1.0f}
	};

    // Define cube face indices (ensure proper orientation)
    GLushort indices[] = {
	        4, 7, 6, 6, 5, 4, //top
	        0, 1, 2, 2, 3, 0, //bottom
	        0, 3, 7, 7, 4, 0, //left
	        1, 5, 6, 6, 2, 1, //right
	        2, 6, 7, 7, 3, 2, //front
	        0, 4, 5, 5, 1, 0  //back
	};

	// Bind cube positions
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[CubePosBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind cube colors
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[CubeColBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // Bind cube indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[CubeIndexBuffer]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Model vectors
    vector<vec4> mesh_vertices;
    vector<vec2> mesh_uvCoords;
    vector<vec3> mesh_normals;
    // Bind sphere vertex array object
    glBindVertexArray(VAOs[Sphere]);

    // Load sphere model and store number of vertices
    loadOBJ(model, mesh_vertices, mesh_uvCoords, mesh_normals);
    sphereVertices = mesh_vertices.size();

    // Bind sphere positions
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SpherePosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*meshPosCoords*sphereVertices, mesh_vertices.data(), GL_STATIC_DRAW);

}

void display( )
{
	// Clear window and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Compute anisotropic scaling
    GLfloat xratio = 1.0f;
    GLfloat yratio = 1.0f;

    // If taller than wide adjust y
    if (ww <= hh)
    {
        yratio = (GLfloat)hh / (GLfloat)ww;
    }
        // If wider than tall adjust x
    else if (hh <= ww)
    {
        xratio = (GLfloat)ww / (GLfloat)hh;
    }

    // Set projection matrix
    proj_matrix = frustum(-1.0f*xratio, 1.0f*xratio, -1.0f*yratio, 1.0f*yratio, 1.0f, 8.0f);

    // Set camera matrix
    camera_matrix = lookat(eye, center, up);

    // Render objects
	render_scene();

	// Flush pipeline
	glFlush();
}

void render_scene( ) {
    // Declare transformation matrices
    mat4 model_matrix = mat4().identity();
    mat4 scale_matrix = mat4().identity();
    mat4 rot_matrix = mat4().identity();
    mat4 trans_matrix = mat4().identity();

	// Draw cube
	// Set cube transformation matrix
    trans_matrix = translate(vec3(0.0f, 0.0f, 0.0f));
    rot_matrix = rotate(cube_angle, normalize(axis));
    scale_matrix = scale(vec3(1.0f, 1.0f, 1.0f));
	model_matrix = trans_matrix*rot_matrix*scale_matrix;
    // TODO: Select gradient shader program
    glUseProgram(grad_program);

    // Bind Cube vertex array object
    glBindVertexArray(VAOs[Cube]);
    // TODO: Bind attribute buffers and set gradient vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[CubePosBuffer]);
    glVertexAttribPointer(grad_vPos, cubePosCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(grad_vPos);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[CubeColBuffer]);
    glVertexAttribPointer(grad_vCol, cubeColCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(grad_vCol);

    // TODO: Pass projection, camera, and model matrix to grad shader
    glUniformMatrix4fv(grad_proj_mat_loc, 1, GL_FALSE, proj_matrix);
    glUniformMatrix4fv(grad_cam_mat_loc, 1, GL_FALSE, camera_matrix);
    glUniformMatrix4fv(grad_model_mat_loc, 1, GL_FALSE, model_matrix);

    // Draw indexed cube
    glDrawElements(GL_TRIANGLES, cubeIndices, GL_UNSIGNED_SHORT, NULL);

    // Draw sphere
    // Set sphere transformation matrix
    trans_matrix = translate(0.0f, 2.0f, 0.0f);
    rot_matrix = rotate(cube_angle, axis);
    scale_matrix = scale(1.0f, 1.0f, 1.0f);
    model_matrix = trans_matrix*rot_matrix*scale_matrix;

    // TODO: Select mesh shader program
    glUseProgram(mesh_program);

    // TODO: Pass projection, camera, and model matrix to mesh shader
    glUniformMatrix4fv(mesh_model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniformMatrix4fv(mesh_cam_mat_loc, 1, GL_FALSE, camera_matrix);
    glUniformMatrix4fv(mesh_proj_mat_loc, 1, GL_FALSE, proj_matrix);

    // TODO: Pass sphere color to mesh shader
    glUniform4fv(mesh_vCol, 1, sphere_color);
    // Draw mesh sphere
    draw_obj(VAOs[Sphere], Buffers[SpherePosBuffer], sphereVertices);

}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Esc closes window
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }

    // Adjust azimuth
    if (key == GLFW_KEY_A) {
        azimuth += daz;
        if (azimuth > 360.0) {
            azimuth -= 360.0;
        }
    } else if (key == GLFW_KEY_D) {
        azimuth -= daz;
        if (azimuth < 0.0)
        {
            azimuth += 360.0;
        }
    }

    // Adjust elevation angle
    if (key == GLFW_KEY_W)
    {
        elevation += del;
        if (elevation > 180.0)
        {
            elevation = 179.0;
        }
    }
    else if (key == GLFW_KEY_S)
    {
        elevation -= del;
        if (elevation < 0.0)
        {
            elevation = 1.0;
        }
    }

    // Adjust radius (zoom)
    if (key == GLFW_KEY_X)
    {
        radius += dr;
    }
    else if (key == GLFW_KEY_Z)
    {
        radius -= dr;
        if (radius < min_radius)
        {
            radius = min_radius;
        }
    }

    // Compute updated camera position
    GLfloat x, y, z;
    x = (GLfloat)(radius*sin(azimuth*DEG2RAD)*sin(elevation*DEG2RAD));
    y = (GLfloat)(radius*cos(elevation*DEG2RAD));
    z = (GLfloat)(radius*cos(azimuth*DEG2RAD)*sin(elevation*DEG2RAD));
    eye = vec3(x,y,z);
}

void mouse_callback(GLFWwindow *window, int button, int action, int mods){

}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // TODO: Store new window sizes in global variables
    ww = width;
    hh = height;
}

void draw_obj(GLuint VAO, GLuint Buffer, int numVert) {
    // Bind vertex array object and vertex buffer
    glBindVertexArray(VAO);
    // TODO: Bind attribute buffers and set mesh vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, Buffer);
    glVertexAttribPointer(mesh_vPos, meshPosCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(mesh_vPos);
    // Draw mesh
    glDrawArrays(GL_TRIANGLES, 0, numVert);
}
