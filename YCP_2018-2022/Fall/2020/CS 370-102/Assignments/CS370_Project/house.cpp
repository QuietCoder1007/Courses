// CS370 Final Project
// Fall 2020

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"	// Sean Barrett's image loader - http://nothings.org/
#include <stdio.h>
//#include <irrKlang>
#include "glerror_utility.h"
#include <vector>
#include "vgl.h"
#include "objloader.h"
#include "utils.h"
#include "vmath.h"
#include "lighting.h"
#include "particle.h"
#define DEG2RAD (M_PI/180.0)

using namespace vmath;
using namespace std;

enum VAO_IDs {Cone, Cube, Cylinder, Donut, Octahedron, Sphere, Torus, NumVAOs};
enum Buffer_IDs {ConePosBuffer, CubePosBuffer, CylinderPosBuffer, DonutPosBuffer, OctaPosBuffer, SpherePosBuffer, TorusPosBuffer, NumBuffers};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

GLint numVertices[NumVAOs];
GLint posCoords = 4;
vec4 wall_color = {1.0f, 1.0f, 0.0f,1.0f};
vec4 tree_color = {0.63f, 0.32f, 0.18f,1.0f};
vec4 stone_color = {0.5f, 0.5f, 0.0f,1.0f};
vec4 donut_color = {1.0f, 0.75f, 0.8f,1.0f};
vec4 grass_color = {0.0f, 0.75f, 0.1f,1.0f};

// Camera
vec3 eye = {3.0f, 3.0f, 0.0f};
vec3 center = {0.0f, 0.0f, 0.0f};
vec3 up = {0.0f, 1.0f, 0.0f};

// Shader variables
GLuint program;
GLuint vPos;
GLuint vCol;
GLuint model_mat_loc;
GLuint proj_mat_loc;
GLuint cam_mat_loc;
const char *vertex_shader = "../color_mesh.vert";
const char *frag_shader = "../color_mesh.frag";

// Global state
const char *models[NumVAOs] = {"../models/cone.obj", "../models/cube.obj", "../models/cylinder.obj", "../models/donut.obj", "../models/octahedron.obj", "../models/sphere.obj", "../models/torus.obj", };
mat4 proj_matrix;
mat4 camera_matrix;
vec3 axis = {0.0f, 1.0f, 0.0f};

// Global spherical coord values
GLfloat azimuth = 0.0f;
GLfloat daz = 2.0f;
GLfloat elevation = 90.0f;
GLfloat del = 2.0f;
GLfloat radius = 3.0f;
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
    try {
        // Create OpenGL window
        GLFWwindow *window = CreateWindow("Think Inside The Box");
        if (!window) {
            fprintf(stderr, "ERROR: could not open window with GLFW3\n");
            glfwTerminate();
            return 1;
        } else {
            printf("OpenGL window successfully created\n");
        }

        // Store initial window size
        glfwGetFramebufferSize(window, &ww, &hh);

        // Register callbacks
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetKeyCallback(window, key_callback);
        glfwSetMouseButtonCallback(window, mouse_callback);

        // Create geometry buffers
        build_geometry();

        // Load shaders and associate shader variables
        ShaderInfo shaders[] = {{GL_VERTEX_SHADER,   vertex_shader},
                                {GL_FRAGMENT_SHADER, frag_shader},
                                {GL_NONE, NULL}};
        program = LoadShaders(shaders);
        vPos = glGetAttribLocation(program, "vPosition");
        vCol = glGetUniformLocation(program, "vColor");
        model_mat_loc = glGetUniformLocation(program, "model_matrix");
        proj_mat_loc = glGetUniformLocation(program, "proj_matrix");
        cam_mat_loc = glGetUniformLocation(program, "camera_matrix");

        // Enable depth test
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);

        // Set Initial camera position
        GLfloat x, y, z;
        x = (GLfloat) (radius * sin(azimuth * DEG2RAD) * sin(elevation * DEG2RAD));
        y = (GLfloat) (radius * cos(elevation * DEG2RAD));
        z = (GLfloat) (radius * cos(azimuth * DEG2RAD) * sin(elevation * DEG2RAD));
        eye = vec3(x, y, z);

        // Start loop
        while (!glfwWindowShouldClose(window)) {
            // Draw graphics
            display();
            // Update other events like input handling
            glfwPollEvents();
            // Swap buffer onto screen
            glfwSwapBuffers(window);
        }

    } catch (const std::exception & e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    // Close window
    glfwTerminate();
    return 0;
}

void build_geometry( )
{
    // Model vectors
    vector<vec4> vertices;
    vector<vec2> uvCoords;
    vector<vec3> normals;

    // Generate vertex arrays and buffers
    glGenVertexArrays(NumVAOs, VAOs);
    glGenBuffers(NumBuffers, Buffers);

    // Bind cube vertex array
    glBindVertexArray(VAOs[Cube]);

    // TODO: Load cube model and store number of vertices
    loadOBJ(models[Cube], vertices, uvCoords, normals);
    numVertices[Cube] = vertices.size();

    // Bind cone vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[CubePosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*posCoords*numVertices[Cube], vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(VAOs[Cone]);

    // TODO: Load cone model and store number of vertices
    loadOBJ(models[Cone], vertices, uvCoords, normals);
    numVertices[Cone] = vertices.size();

    // Bind cube vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ConePosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*posCoords*numVertices[Cone], vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(VAOs[Cylinder]);

    // TODO: Load cylinder model and store number of vertices
    loadOBJ(models[Cylinder], vertices, uvCoords, normals);
    numVertices[Cylinder] = vertices.size();

    // Bind cube vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[CylinderPosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*posCoords*numVertices[Cylinder], vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(VAOs[Donut]);

    // TODO: Load donut model and store number of vertices
    loadOBJ(models[Donut], vertices, uvCoords, normals);
    numVertices[Donut] = vertices.size();

    // Bind cube vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[DonutPosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*posCoords*numVertices[Donut], vertices.data(), GL_STATIC_DRAW);


    glBindVertexArray(VAOs[Octahedron]);

    // TODO: Load octahedron model and store number of vertices
    loadOBJ(models[Octahedron], vertices, uvCoords, normals);
    numVertices[Octahedron] = vertices.size();

    // Bind cube vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[OctaPosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*posCoords*numVertices[Octahedron], vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(VAOs[Sphere]);

    // TODO: Load sphere model and store number of vertices
    loadOBJ(models[Sphere], vertices, uvCoords, normals);
    numVertices[Sphere] = vertices.size();

    // Bind cube vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SpherePosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*posCoords*numVertices[Sphere], vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(VAOs[Torus]);

    // TODO: Load torus model and store number of vertices
    loadOBJ(models[Torus], vertices, uvCoords, normals);
    numVertices[Torus] = vertices.size();

    // Bind cube vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[TorusPosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*posCoords*numVertices[Torus], vertices.data(), GL_STATIC_DRAW);
}

void display( )
{
    // Declare projection and camera matrices
    proj_matrix = mat4().identity();
    camera_matrix = mat4().identity();

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

    // TODO: Set perspective projection matrix
    proj_matrix = ortho(-6.0f*xratio, 6.0f*xratio, -6.0f*yratio, 6.0f*yratio, -6.0f, 16.0f);

    // TODO: Set camera matrix
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

    // Select shader program
    glUseProgram(program);
    // Pass projection matrix to shader
    glUniformMatrix4fv(proj_mat_loc, 1, GL_FALSE, proj_matrix);
    // Pass camera matrix to shader
    glUniformMatrix4fv(cam_mat_loc, 1, GL_FALSE, camera_matrix);

    // Set cube transformation matrix
    trans_matrix = translate(0.0f, 0.50f, 2.25f);
    rot_matrix = rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));
    scale_matrix = scale(2.0f, 0.5f, 2.0f);
	model_matrix = trans_matrix*rot_matrix*scale_matrix;
	glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
	glUniform4fv(vCol, 1, wall_color);

	// TODO: Draw cube
	draw_obj(VAOs[Cube], Buffers[CubePosBuffer], numVertices[Cube]);

    // Set cube transformation matrix
    trans_matrix = translate(0.0f, 0.50f, -2.25f);
    rot_matrix = rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));
    scale_matrix = scale(2.0f, 0.5f, 2.0f);
	model_matrix = trans_matrix*rot_matrix*scale_matrix;
	glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
	glUniform4fv(vCol, 1, wall_color);

	// TODO: Draw cube
	draw_obj(VAOs[Cube], Buffers[CubePosBuffer], numVertices[Cube]);

    // Set cube transformation matrix
    trans_matrix = translate(2.25f, 0.50f, 0.0f);
    rot_matrix = rotate(90.0f, vec3(0.0f, 0.0f, 1.0f));
    scale_matrix = scale(2.0f, 0.5f, 2.0f);
	model_matrix = trans_matrix*rot_matrix*scale_matrix;
	glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
	glUniform4fv(vCol, 1, wall_color);

	// TODO: Draw cube
	draw_obj(VAOs[Cube], Buffers[CubePosBuffer], numVertices[Cube]);

    // Set cube transformation matrix
    trans_matrix = translate(-2.25f, 0.50f, 0.0f);
    rot_matrix = rotate(90.0f, vec3(0.0f, 0.0f, 1.0f));
    scale_matrix = scale(2.0f, 0.5f, 2.0f);
	model_matrix = trans_matrix*rot_matrix*scale_matrix;
	glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
	glUniform4fv(vCol, 1, wall_color);

	// TODO: Draw cube
	draw_obj(VAOs[Cube], Buffers[CubePosBuffer], numVertices[Cube]);

    // TODO: FLOOR
    // Set cube transformation matrix
    trans_matrix = translate(0.0f, -1.75f, 0.0f);
    rot_matrix = rotate(0.0f, vec3(0.0f, 1.0f, 0.0f));
    scale_matrix = scale(2.0f, 0.5f, 2.0f);
	model_matrix = trans_matrix*rot_matrix*scale_matrix;
	glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
	glUniform4fv(vCol, 1, wall_color);

	// TODO: Draw cube
	draw_obj(VAOs[Cube], Buffers[CubePosBuffer], numVertices[Cube]);


    // TODO: Tree
    // Set cube transformation matrix
    trans_matrix = translate(0.0f, 0.50f, 0.0f);
    rot_matrix = rotate(0.0f, vec3(0.0f, 1.0f, 0.0f));
    scale_matrix = scale(0.250f, 1.0f, 0.250f);
    model_matrix = trans_matrix*rot_matrix*scale_matrix;
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniform4fv(vCol, 1, tree_color);

    draw_obj(VAOs[Cylinder], Buffers[CylinderPosBuffer], numVertices[Cylinder]);

    // TODO: Donut
    // Set Donut transformation matrix
    trans_matrix = translate(0.0f, 3.50f, 0.0f);
    rot_matrix = rotate(0.0f, vec3(0.0f, 1.0f, 0.0f));
    scale_matrix = scale(1.0f, 1.0f, 1.0f);
    model_matrix = trans_matrix*rot_matrix*scale_matrix;
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniform4fv(vCol, 1, tree_color);

//    draw_obj(VAOs[Donut], Buffers[DonutPosBuffer], numVertices[Donut]);
//    thigle(EXC_MSG("Failed to draw Donut"));

    // TODO: GRASS
    // Set cube transformation matrix
    trans_matrix = translate(9.0f, -3.0f, 0.0f);
    rot_matrix = rotate(0.0f, vec3(0.0f, 1.0f, 0.0f));
    scale_matrix = scale(2.0f, 0.5f, 2.0f);
    model_matrix = trans_matrix*rot_matrix*scale_matrix;
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniform4fv(vCol, 1, grass_color);

    // TODO: Draw cube
    draw_obj(VAOs[Cube], Buffers[CubePosBuffer], numVertices[Cube]);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // ESC to quit
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
    glViewport(0, 0, width, height);

    ww = width;
    hh = height;
}

//void load_object(GLuint obj) {
//    vector<vec4> vertices;
//    vector<vec2> uvCoords;
//    vector<vec3> normals;
//
//    loadOBJ(objFiles[obj], vertices, uvCoords, normals);
//    numVertices[obj] = vertices.size();
//    // Create and load object buffers
//    glGenBuffers(NumObjBuffers, ObjBuffers[obj]);
//    glBindVertexArray(VAOs[obj]);
//    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[obj][PosBuffer]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*posCoords*numVertices[obj], vertices.data(), GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[obj][NormBuffer]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*normCoords*numVertices[obj], normals.data(), GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//}

void draw_obj(GLuint VAO, GLuint Buffer, int numVert) {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, Buffer);
    glVertexAttribPointer(vPos, posCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vPos);
    glDrawArrays(GL_TRIANGLES, 0, numVert);
}
