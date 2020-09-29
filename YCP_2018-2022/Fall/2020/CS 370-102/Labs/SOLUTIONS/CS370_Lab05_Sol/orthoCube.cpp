#include "stdio.h"
#include "vgl.h"
#include "utils.h"
#include "vmath.h"

using namespace vmath;

enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {PosBuffer, ColBuffer, IndexBuffer, NumBuffers};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

GLint numVertices = 8;
GLint posCoords = 3;
GLint colCoords = 4;
GLint numIndices = 36;

// Shader variables
GLuint program;
GLuint vPos;
GLuint vCol;
GLuint model_mat_loc;
GLuint proj_mat_loc;
const char *vertex_shader = "../trans.vert";
const char *frag_shader = "../trans.frag";

// Global state
GLfloat cube_angle = 0.0;
GLdouble elTime = 0.0;
GLdouble rpm = 10.0;
vec3 axis = {1.0f, 1.0f, 1.0f};

// Global screen dimensions
GLint ww,hh;

void build_geometry( );
void display( );
void render_scene( );
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, int button, int action, int mods);

int main(int argc, char**argv)
{
	// Create OpenGL window
	GLFWwindow* window = CreateWindow("Ortho Cube");
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    } else {
        printf("OpenGL window successfully created\n");
    }

    // TODO: Store initial window size in global variables
    glfwGetFramebufferSize(window, &ww, &hh);

    // Register callbacks
    glfwSetKeyCallback(window,key_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);
	// TODO: Register resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Get initial time
    elTime = glfwGetTime();

    // Create geometry buffers
    build_geometry();
    
    // Load shaders and associate variables
	ShaderInfo shaders[] = { {GL_VERTEX_SHADER, vertex_shader},{GL_FRAGMENT_SHADER, frag_shader},{GL_NONE, NULL} };
	program = LoadShaders(shaders);
	vPos = glGetAttribLocation(program, "vPosition");
    vCol = glGetAttribLocation(program, "vColor");
    model_mat_loc = glGetUniformLocation(program, "model_matrix");
    proj_mat_loc = glGetUniformLocation(program, "proj_matrix");

    // TODO: Enable depth test
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

	// Start loop
    while ( !glfwWindowShouldClose( window ) ) {
    	// Draw graphics
        display();
        // Update other events like input handling
        glfwPollEvents();
        // Update angle based on time for fixed rpm
        GLdouble curTime = glfwGetTime();
        cube_angle += (curTime-elTime)*(rpm/60.0)*360.0;
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
    // Generate and bind vertex arrays
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

    // Define 3D vertices for cube
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

	// Define vertex colors
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

    // TODO: Define face indices (ensure proper orientation)
    GLushort indices[] = {
	        4, 7, 6, 6, 5, 4, //top
	        0, 1, 2, 2, 3, 0, //bottom
	        0, 3, 7, 7, 4, 0, //left
	        1, 5, 6, 6, 2, 1, //right
	        2, 6, 7, 7, 3, 2, //front
	        0, 4, 5, 5, 1, 0  //back
	};

    // Generate vertex buffers
	glGenBuffers(NumBuffers, Buffers);

	// Bind vertex positions
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[PosBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind vertex colors
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ColBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // Bind cube indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[IndexBuffer]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

}

void display( )
{
    // Declare projection matrix
    mat4 proj_matrix = mat4().identity();

	// TODO: Clear window and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO: Compute anisotropic scaling
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

    // TODO: Set projection matrix
    proj_matrix = ortho(-2.0f*xratio, 2.0f*xratio, -2.0f*yratio, 2.0f*yratio, -2.0f, 2.0f);

    // Pass projection matrix to shader
    glUniformMatrix4fv(proj_mat_loc, 1, GL_FALSE, proj_matrix);

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

    // Select shader program and bind vertex array and buffer
    glUseProgram(program);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[PosBuffer]);
    glVertexAttribPointer(vPos, posCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vPos);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ColBuffer]);
    glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vCol);

	// Draw cube
    trans_matrix = translate(vec3(0.0f, 0.0f, 0.0f));
    rot_matrix = rotate(cube_angle, normalize(axis));
    scale_matrix = scale(vec3(1.0f, 1.0f, 1.0f));
	model_matrix = trans_matrix*rot_matrix*scale_matrix;
	glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
	glBindVertexArray(VAOs[Triangles]);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, NULL);

}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Esc closes window
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }
}

void mouse_callback(GLFWwindow *window, int button, int action, int mods){

}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // TODO: Store new window sizes in global variables
    ww = width;
    hh = height;
}
