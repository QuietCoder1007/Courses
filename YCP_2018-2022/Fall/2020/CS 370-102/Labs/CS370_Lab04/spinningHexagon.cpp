#include "stdio.h"
#include "vgl.h"
#include "utils.h"
#include "vmath.h"

using namespace vmath;

enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {PosBuffer, IndexBuffer, NumBuffers};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

GLint posCoords = 2;
GLint numIndices = 12;

// Shader variables
GLuint program;
GLuint vPos;
GLuint col;
GLuint model_mat_loc;
const char *vertex_shader = "../trans.vert";
const char *frag_shader = "../trans.frag";

// Global state
GLfloat hex_angle = 0.0;
GLfloat hex_x = 0.0;
GLfloat hex_y = 0.0;
GLfloat delta = 0.1;
GLdouble elTime = 0.0;
GLdouble rpm = 10.0;
GLint dir = 1;

void build_geometry( );
void display( );
void render_scene( );
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, int button, int action, int mods);

int main(int argc, char**argv)
{
	// Create OpenGL window
	GLFWwindow* window = CreateWindow("Transform Hexagon");
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    } else {
        printf("OpenGL window successfully created\n");
    }

    // TODO: Register callbacks

    // TODO: Get initial time

	// Create geometry buffers
    build_geometry();
    
    // Load shaders and associate variables
    ShaderInfo shaders[] = { {GL_VERTEX_SHADER, vertex_shader},{GL_FRAGMENT_SHADER, frag_shader},{GL_NONE, NULL} };
    program = LoadShaders(shaders);
    vPos = glGetAttribLocation(program, "vPosition");
    col = glGetUniformLocation(program, "color");
    model_mat_loc = glGetUniformLocation(program, "model_matrix");

	// Start loop
    while ( !glfwWindowShouldClose( window ) ) {
    	// Draw graphics
        display();
        // Update other events like input handling
        glfwPollEvents();
        //  TODO: Update angle based on time for fixed rpm

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

    // Define vertices (no particular orientation)
    GLfloat vertices[][2] = {
            {1.0f, 0.0f},
            {0.5f, 0.866f},
            {-0.5f, 0.866f},
            {-1.0f, 0.0f},
            {-0.5f, -0.866f},
            {0.5f, -0.866f}
    };

    // Define face indices (ensure proper orientation)
    GLushort indices[] = {
            0, 1, 2,
            2, 3, 4,
            4, 5, 0,
            0, 2, 4
    };

    // Generate vertex buffers
    glGenBuffers(NumBuffers, Buffers);

    // Bind vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[PosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind hexagon indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[IndexBuffer]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

}

void display( )
{
	// Clear window
	glClear(GL_COLOR_BUFFER_BIT);

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
    glBindVertexArray(VAOs[Triangles]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[PosBuffer]);
    glVertexAttribPointer(vPos, posCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vPos);

    // Draw hexagon
    // TODO: Set translation matrix

    // TODO: Set rotation matrix

    scale_matrix = scale(0.5f);
    model_matrix = trans_matrix*rot_matrix*scale_matrix;
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniform3fv(col, 1, vec3(1.0f,0.0f,0.0f));
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, NULL);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Esc closes window
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }

    // TODO: Move hexagon with arrow keys

}

void mouse_callback(GLFWwindow *window, int button, int action, int mods){
    // TODO: Flip spin direction with mouse click

}

