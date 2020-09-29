#include "stdio.h"
#include "vgl.h"
#include "utils.h"

int main(int argc, char**argv)
{
	// Create OpenGL window
	GLFWwindow* window = CreateWindow("Hello OpenGL!");
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    } else {
        printf("OpenGL window successfully created\n");
    }

    // Start loop
    while ( !glfwWindowShouldClose( window ) ) {
		// Retrieve any UI events
        glfwPollEvents();
    }

    // Close window
    glfwTerminate();
    return 0;
}
