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

void build_geometry( );
void display( );
void render_scene( );

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

	// Create geometry buffers
    build_geometry();
    
    // Load shaders and associate shader variables
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
	mat4 model_matrix;
	mat4 scale_matrix;
	mat4 rot_matrix;
	mat4 trans_matrix;

    vec3 scale_factors;
    vec3 rot_axii;
    vec3 trans_delta;

    // Select shader program and bind vertex array and buffer
    glUseProgram(program);
    glBindVertexArray(VAOs[Triangles]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[PosBuffer]);
    glVertexAttribPointer(vPos, posCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vPos);

	// Draw base hexagon
//	model_matrix = mat4().identity();
//	glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
//	glUniform3fv(col, 1, vec3(1.0f,0.0f,0.0f));
//	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, NULL);

    // TODO: Draw scaled hexagon
//    scale_factors = vec3(0.5f, 0.5f, 1.0f);
//
//    scale_matrix = scale(scale_factors);
//    model_matrix = scale_matrix;
//
//    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
//    glUniform3fv(col, 1, vec3(0.0f,1.0f,0.0f));
//    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, NULL);

    // TODO: Draw scaled/rotated hexagon
    rot_axii = vec3(0.0f,0.0f,1.0f);
    scale_factors = vec3(0.25f, 0.25f, 1.0f);

    rot_matrix = rotate(90.0f, rot_axii);
    scale_matrix = scale(scale_factors);

    model_matrix = rot_matrix * scale_matrix;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniform3fv(col, 1, vec3(0.0f,0.0f,1.0f));
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, NULL);

    // TODO: Draw scaled/rotated/translated hexagon
    trans_delta = vec3(-2.0f,2.0f,1.0f);
    rot_axii    = vec3(0.0f,0.0f,1.0f);
    scale_factors = vec3(0.25f, 0.25f, 1.0f);

    trans_matrix = translate(trans_delta);
    scale_matrix = scale( scale_factors);
    rot_matrix   = rotate(90.0f, rot_axii);

    model_matrix = trans_matrix * rot_matrix * scale_matrix;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniform3fv(col, 1, vec3(1.0f,1.0f,0.0f));
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, NULL);

}

