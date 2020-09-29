#include "stdio.h"
#include "vgl.h"
#include "utils.h"

enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {PosBuffer, ColBuffer, IndexBuffer, NumBuffers};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

GLint posCoords = 2;
GLint colCoords = 4;
GLint numIndices = 12;

// Shader variables
GLuint program;
GLuint vPos;
GLuint vCol;
const char *vertex_shader = "../basic.vert";
const char *frag_shader = "../basic.frag";

void build_geometry( );
void display( );
void render_scene( );

int main(int argc, char**argv)
{
	// Create OpenGL window
	GLFWwindow* window = CreateWindow("Shaded Hexagon");
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
    vCol = glGetAttribLocation(program, "vColor");

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

	// TODO: Define colors per vertex

	// TODO: Define face indices (ensure proper orientation)

	// Generate vertex buffers
	glGenBuffers(NumBuffers, Buffers);

	// Bind vertex positions
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[PosBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // TODO: Bind vertex colors

    // TODO: Bind indices

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

void render_scene() {
	// Select shader program and bind vertex array and buffer
	glUseProgram(program);
    glBindVertexArray(VAOs[Triangles]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[PosBuffer]);
    glVertexAttribPointer(vPos, posCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vPos);
	// TODO: Bind color buffer

	// TODO: Draw indexed geometry

}

