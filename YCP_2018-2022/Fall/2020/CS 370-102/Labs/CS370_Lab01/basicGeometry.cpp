#include "stdio.h"
#include "vgl.h"
#include "utils.h"

enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {PosBuffer, NumBuffers};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

GLint numVertices = 6;
GLint posCoords = 2;

const GLfloat rotate_ninety_matrix [4][2] = { {1, -1}, {-1, 1}, {1, -1}, {-1, 1} };
const GLfloat rotate_one_eighty_matrix [4][2] = { {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1} };
const GLfloat rotate_minus_ninety_matrix [4][2] = { {-1, 1}, {1, -1}, {-1, 1}, {1, -1} };

// Shader variables
GLuint program;
GLuint vPos;
const char *vertex_shader = "../basic.vert";
const char *frag_shader = "../basic.frag";

void build_geometry( );
void display( );
void render_scene( );

int main(int argc, char**argv)
{
	// Create OpenGL window
	GLFWwindow* window = CreateWindow("Basic Geometry");
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    } else {
        printf("OpenGL window successfully created\n");
    }

	// Create geometry buffers
    build_geometry();

    // Load shaders and associate shader variables
	ShaderInfo shaders[] = { {GL_VERTEX_SHADER, vertex_shader},{GL_FRAGMENT_SHADER, frag_shader},{GL_NONE, NULL} };
	program = LoadShaders(shaders);
	vPos = glGetAttribLocation(program, "vPosition");

    // Start loop
    while ( !glfwWindowShouldClose( window ) ) {
        // Draw graphics
        display();
        // Update other events like input handling
        glfwPollEvents();
        // Swap buffer onto screen
        glfwSwapBuffers( window );
    }

    // Close window
    glfwTerminate();
    return 0;
}

void build_geometry( )
{
	// TODO: Generate and bind vertex arrays
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);

    // TODO: Define vertices (ensure proper orientation)
    GLfloat vertices[][2] = {
            {-0.5f,-0.5f},
            { 0.5f, 0.5f},
            {-0.5f, 0.5f},
            {-0.5f,-0.5f},
            { 0.5f,-0.5f},
            { 0.5f, 0.5f}
    };


	// TODO: Generate and bind vertex buffers
	glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[PosBuffer]);

	// TODO: Load vertex data into buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void display( )
{
    // TODO: Clear window
    glClear(GL_COLOR_BUFFER_BIT);

    // TODO: Render objects
    render_scene();

    // TODO: Flush pipeline
    glFlush();
}

void render_scene( ) {

	// TODO: Select shader program and bind vertex array and buffer
    glUseProgram(program);
    glBindVertexArray(VAOs[Triangles]);
    glBindBuffer(GL_ARRAY_BUFFER , Buffers[PosBuffer]);
    glVertexAttribPointer(vPos, posCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vPos);

	// TODO: Draw geometry
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

GLfloat[][] rotateNinetyDegrees(GLfloat array){

}