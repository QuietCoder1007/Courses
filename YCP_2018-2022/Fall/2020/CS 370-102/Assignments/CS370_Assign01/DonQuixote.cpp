// CS370 Assignment 1 - Don Quixote
// Fall 2020

#include "stdio.h"
#include "vgl.h"
#include "utils.h"
#include "vmath.h"

using namespace vmath;
using namespace std;

enum VAO_IDs {Square, Sun, NumVAOs};
enum Buffer_IDs {SqPosBuffer, SqSkyColBuffer, SqGrassColBuffer, SqHouseColBuffer, TriRoofColBuffer, TriBladeColBuffer, SqIndexBuffer, SunPosBuffer, SunColBuffer, NumBuffers, };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

GLint posCoords = 2;
GLint colCoords = 4;
GLint numSqIndices = 6;
GLint numTriIndices = 3;

// Shader variables
GLuint program;
GLuint vPos;
GLuint vCol;
GLuint model_mat_loc;
const char *vertex_shader = "../trans.vert";
const char *frag_shader = "../trans.frag";

// Global Variables
GLfloat sun_size_x;
GLfloat sun_size_y;
GLfloat sunray_size_x;
GLfloat sunray_size_y;
GLint space_cntr = 0;
GLfloat hex_angle = 0.0;
GLfloat delta = 0.1;
GLdouble elTime = 0.0;
GLdouble rpm = 10.0;
GLint dir = 1;
GLint prev_dir = 0;

void build_geometry( );
void display( );
void render_scene( );
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, int button, int action, int mods);

int main(int argc, char**argv)
{
    // Create OpenGL window
    GLFWwindow* window = CreateWindow("Don Quixote");
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    } else {
        printf("OpenGL window successfully created\n");
    }

    // TODO: Register callbacks
    glfwSetMouseButtonCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);

    // Create geometry buffers
    build_geometry();

    // Load shaders and associate variables
    ShaderInfo shaders[] = { {GL_VERTEX_SHADER, vertex_shader},{GL_FRAGMENT_SHADER, frag_shader},{GL_NONE, NULL} };
    program = LoadShaders(shaders);
    vPos = glGetAttribLocation(program, "vPosition");
    vCol = glGetAttribLocation(program, "vColor");
    model_mat_loc = glGetUniformLocation(program, "model_matrix");

    // Start loop
    while ( !glfwWindowShouldClose( window ) ) {
        // Draw graphics
        display();
        // Update other events like input handling
        glfwPollEvents();
        //  TODO: Update angle1 based on time for fixed rpm when animating
        GLdouble curTime = glfwGetTime();
        hex_angle += dir*(curTime-elTime)*(rpm/60.0)*360.0;
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
    glBindVertexArray(VAOs[Square]);

    // Define square vertices
    GLfloat sqVertices[][2] = {
            { 1.0f, 1.0f},
            {-1.0f, 1.0f},
            {-1.0f,-1.0f},
            { 1.0f,-1.0f}
    };

    // TODO: Define gradient colors
    GLfloat skyGradient[][4] = {
            { 0.60f, 0.93f, 1.00f, 1.00f },
            { 0.60f, 0.93f, 1.00f, 1.00f },
            { 0.00f, 0.00f, 0.70f, 1.00f },
            { 0.00f, 0.00f, 0.70f, 1.00f }
    };

    GLfloat grassGradient[][4] = {
            { 0.05f, 0.30f, 0.00f, 1.00f },
            { 0.678f, 1.000f, 0.184f, 1.00f },
            { 0.678f, 1.000f, 0.184f, 1.00f },
            { 0.05f, 0.30f, 0.00f, 1.00f }
    };

    GLfloat bladeGradient[][4] = {
            { 0.902, 0.902, 0.980, 1.00 },
            { 0.902, 0.902, 0.980, 1.00 },
            { 0.902, 0.902, 0.980, 1.00 },
            { 0.902, 0.902, 0.980, 1.00 }
    };

    // TODO: Define solid colors
    GLfloat houseSolid[][4]{
            { 0.502, 0.000, 0.000 , 7.00 },
            { 0.502, 0.000, 0.000 , 7.00 },
            { 0.502, 0.000, 0.000 , 7.00 },
            { 0.502, 0.000, 0.000 , 7.00 }
    };
    GLfloat roofSolid[][4]{
            { 0.627, 0.322, 0.176 , 8.00 },
            { 0.627, 0.322, 0.176 , 8.00 },
            { 0.627, 0.322, 0.176 , 8.00 },
            { 0.627, 0.322, 0.176 , 8.00 }
    };
    // TODO: Define face indices (ensure proper orientation)
    GLushort sqIndices[]{
            0,1,2,
            2,3,0
    };

    // Generate vertex buffers
    glGenBuffers(NumBuffers, Buffers);

    // TODO: Bind square vertex and color buffers
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqPosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sqVertices), sqVertices, GL_STATIC_DRAW);

    // TODO: COLORS
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqSkyColBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyGradient), skyGradient, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqGrassColBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(grassGradient), grassGradient, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqHouseColBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(houseSolid), houseSolid, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[TriRoofColBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(roofSolid), roofSolid, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[TriBladeColBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bladeGradient), bladeGradient, GL_STATIC_DRAW);

    // TODO: Bind square indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[SqIndexBuffer]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sqIndices), sqIndices, GL_STATIC_DRAW);

    // Create sun
    glBindVertexArray(VAOs[Sun]);

    // TODO: Define sun vertices and colors

    GLfloat sunVertices[][2]{
            { -0.50f, 0.50f},
            { -0.50f, 0.00f},
            { 0.00f, 0.50f}
    };

    GLfloat sunGradient[][4] = {
            { 1.000, 0.840, 0.000, 1.00 },
            { 1.000, 1.000, 0.900, 1.00 },
            { 1.000, 0.840, 0.000, 1.00 },
            { 1.000, 1.000, 0.900, 1.00 }
    };

    // TODO: Bind sun vertex and color buffers
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SunPosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sunVertices), sunVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SunColBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sunGradient), sunGradient, GL_STATIC_DRAW);

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
    // TODO: Declare transformation matrices
    mat4 model_matrix = mat4().identity();
    mat4 scale_matrix1;
    mat4 scale_matrix2;
    mat4 rot_matrix1;
    mat4 rot_matrix2;
    mat4 rot_matrix3;
    mat4 trans_matrix1;
    mat4 trans_matrix2;
    mat4 trans_matrix3;

    vec3 scale_xyz1;
    vec3 scale_xyz2;
    GLfloat angle1;
    GLfloat angle2;
    vec3 rotate_xyz1;
    vec3 rotate_xyz2;
    vec3 rotate_xyz3;
    vec3 trans_xyz1;
    vec3 trans_xyz2;
    vec3 trans_xyz3;

    // Select shader program
    glUseProgram(program);

    // TODO: Draw squares
    glBindVertexArray(VAOs[Square]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqPosBuffer]);
    glVertexAttribPointer(vPos, posCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vPos);

    // TODO: Draw sky
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqSkyColBuffer]);
    glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vCol);

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glDrawElements(GL_TRIANGLES, numSqIndices, GL_UNSIGNED_SHORT, NULL);

    // TODO: Draw Grass
    trans_xyz1 = vec3(0.00f, -1.50f, 0.00f);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqGrassColBuffer]);
    glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vCol);
    trans_matrix1 = translate(trans_xyz1);
    model_matrix = trans_matrix1;
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glDrawElements(GL_TRIANGLES, numSqIndices, GL_UNSIGNED_SHORT, NULL);

    // TODO: Draw House
    trans_xyz1 = vec3(0.00f, -0.30f, 0.00f);
    scale_xyz1 = vec3(0.30f, 0.30f, 1.00f);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqHouseColBuffer]);
    glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vCol);

    trans_matrix1 = translate(trans_xyz1);
    scale_matrix1 = scale(scale_xyz1);
    model_matrix = trans_matrix1*scale_matrix1;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glDrawElements(GL_TRIANGLES, numSqIndices, GL_UNSIGNED_SHORT, NULL);

    // TODO: Draw Roof (using first three square vertices)
    trans_xyz1 = vec3(0.00f, 0.00f, 0.00f);
    scale_xyz1 = vec3(0.30f, 0.30f, 1.00f);
    angle1 = -45.00f;
    rotate_xyz1 = vec3(0.00f, 0.00f, 1.00f);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[TriRoofColBuffer]);
    glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vCol);

    trans_matrix1 = translate(trans_xyz1);
    scale_matrix1 = scale(scale_xyz1);
    rot_matrix1 = rotate(angle1, rotate_xyz1);

    model_matrix = trans_matrix1*rot_matrix1*scale_matrix1;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glDrawElements(GL_TRIANGLES, numTriIndices, GL_UNSIGNED_SHORT, NULL);

    // TODO: Draw fan (using first three square vertices)

    // Set transformation matrix for first blade
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[TriBladeColBuffer]);
    glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vCol);

    trans_xyz1 = vec3(0.00f, 0.0f, 0.00f);
    trans_xyz2 = vec3(0.50f, 1.00f, 0.00f);

    scale_xyz1 = vec3(sqrtf(2)/32, sqrtf(2)/8, 1.00f);
    scale_xyz2 = vec3(0.30f, 0.30f, 1.00f);

    angle1 = -00.00f;
    angle2 = 90.00f;

    rotate_xyz1 = vec3(0.00f, 0.00f, 1.00f);
    rotate_xyz2 = vec3(0.00f, 0.00f, 1.00f);

    trans_matrix1 = translate(trans_xyz1);
    trans_matrix2 = translate(trans_xyz2);

    scale_matrix1 = scale(scale_xyz1);

    rot_matrix1 = rotate(hex_angle, rotate_xyz1);
    rot_matrix2 = rotate(angle2, rotate_xyz2);

    model_matrix = rot_matrix1*scale_matrix1*trans_matrix2;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glDrawElements(GL_TRIANGLES, numTriIndices, GL_UNSIGNED_SHORT, NULL);

    // Set transformation matrix for second blade
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[TriBladeColBuffer]);
    glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vCol);

    trans_xyz1 = vec3(0.00f, 0.0f, 0.00f);
    trans_xyz2 = vec3(0.50f, 1.00f, 0.00f);

    scale_xyz1 = vec3(sqrtf(2)/32, sqrtf(2)/8, 1.00f);

    angle1 = -00.00f;
    angle2 = 90.00f;

    rotate_xyz1 = vec3(0.00f, 0.00f, 1.00f);
    rotate_xyz2 = vec3(0.00f, 0.00f, 1.00f);

    trans_matrix1 = translate(trans_xyz1);
    trans_matrix2 = translate(trans_xyz2);

    scale_matrix1 = scale(scale_xyz1);

    rot_matrix1 = rotate(120+hex_angle, rotate_xyz1);
    rot_matrix2 = rotate(angle2, rotate_xyz2);

    model_matrix = rot_matrix1*scale_matrix1*trans_matrix2;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glDrawElements(GL_TRIANGLES, numTriIndices, GL_UNSIGNED_SHORT, NULL);

    // Set transformation matrix for third blade
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[TriBladeColBuffer]);
    glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vCol);

    trans_xyz1 = vec3(0.00f, 0.0f, 0.00f);
    trans_xyz2 = vec3(0.50f, 1.00f, 0.00f);

    scale_xyz1 = vec3(sqrtf(2)/32, sqrtf(2)/8, 1.00f);
    scale_xyz2 = vec3(0.30f, 0.30f, 1.00f);

    angle1 = -00.00f;
    angle2 = 90.00f;

    rotate_xyz1 = vec3(0.00f, 0.00f, 1.00f);
    rotate_xyz2 = vec3(0.00f, 0.00f, 1.00f);

    trans_matrix1 = translate(trans_xyz1);
    trans_matrix2 = translate(trans_xyz2);

    scale_matrix1 = scale(scale_xyz1);

    rot_matrix1 = rotate(-120+hex_angle, rotate_xyz1);
    rot_matrix2 = rotate(angle2, rotate_xyz2);

    model_matrix = rot_matrix1*scale_matrix1*trans_matrix2;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glDrawElements(GL_TRIANGLES, numTriIndices, GL_UNSIGNED_SHORT, NULL);

    // TODO: Draw sun (using triangle fan)

    for(float i = 0.0f; i < 360.00f; i++){
        glBindBuffer(GL_ARRAY_BUFFER, Buffers[SunPosBuffer]);
        glVertexAttribPointer(vPos, posCoords, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(vPos);

        mat4 sun_rot_matrix = mat4().identity();

        glBindBuffer(GL_ARRAY_BUFFER, Buffers[SunColBuffer]);
        glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(vCol);

        angle1 = -45.00f;
        vec3 sun_rotate_xyz = vec3(0.50f, 0.00f, 1.00f);

        rotate_xyz1 = vec3(0.00f, 0.00f, 1.00f);

        trans_xyz1 = vec3(-0.50f, 0.40f, 0.00f);
        trans_xyz2 = vec3(0.50f, 0.00f, 0.00f);
        trans_xyz3 = vec3(0.00f, 0.00f, 0.00f);

        sunray_size_x = 0.250f;
        sunray_size_y - 0.05f;

        scale_xyz1 = vec3(sunray_size_x, sunray_size_y, 1.00f);

        rot_matrix1 = rotate(angle1, sun_rotate_xyz);

        sun_rot_matrix = rotate(i, rotate_xyz1);

        trans_matrix1 = translate(trans_xyz1);
        trans_matrix2 = translate(trans_xyz2);
        scale_matrix1 = scale(scale_xyz1);

        model_matrix = trans_matrix1 * sun_rot_matrix * scale_matrix1 * rot_matrix1 * trans_matrix2;
        glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
        glDrawElements(GL_TRIANGLE_FAN, numTriIndices, GL_UNSIGNED_SHORT, NULL);
    }

    for(float i = 0; i < 360; i++){
        glBindBuffer(GL_ARRAY_BUFFER, Buffers[SunPosBuffer]);
        glVertexAttribPointer(vPos, posCoords, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(vPos);

        mat4 sun_rot_matrix = mat4().identity();

        glBindBuffer(GL_ARRAY_BUFFER, Buffers[SunColBuffer]);
        glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(vCol);

        angle1 = -45.00f;
        vec3 sun_rotate_xyz = vec3(0.50f, 0.00f, 1.00f);

        rotate_xyz1 = vec3(0.00f, 0.00f, 1.00f);
        rotate_xyz2 = vec3(0.00f, 0.00f, 1.00f);
        rotate_xyz3 = vec3(0.00f, 0.00f, 1.00f);

        trans_xyz1 = vec3(-0.50f, 0.40f, 0.00f);
        trans_xyz2 = vec3(0.50f, 0.00f, 0.00f);
        trans_xyz3 = vec3(0.00f, 0.00f, 0.00f);

        sun_size_x = 0.50f;
        sun_size_y = 0.005f;

        scale_xyz1 = vec3(sun_size_x, sun_size_y, 1.00f);

        rot_matrix1 = rotate(angle1, sun_rotate_xyz);
        rot_matrix2 = rotate(angle1, rotate_xyz2);
        rot_matrix3 = rotate(angle1, rotate_xyz3);

        sun_rot_matrix = rotate(i, rotate_xyz1);

        trans_matrix1 = translate(trans_xyz1);
        trans_matrix2 = translate(trans_xyz2);
        scale_matrix1 = scale(scale_xyz1);

        model_matrix = trans_matrix1 * sun_rot_matrix * scale_matrix1 * rot_matrix1 * trans_matrix2;
        glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
        glDrawElements(GL_TRIANGLE_FAN, numTriIndices, GL_UNSIGNED_SHORT, NULL);
    }

}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Esc closes window
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }

    // TODO: Start/Stop animation with spacebar
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && space_cntr%2 == 0) {
        prev_dir = dir;
        dir = 0;
        space_cntr++;
    } else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && space_cntr%2 == 1){
        dir = prev_dir;
        space_cntr++;
    } else if (key == GLFW_KEY_UP && action == GLFW_PRESS){
        sun_size_x += 0.1;
        sun_size_y += 0.1;
        sunray_size_x += 0.1;
        sunray_size_y += 0.1;
    } else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS){
        sun_size_x -= 0.1;
        sun_size_y -= 0.1;
        sunray_size_x -= 0.1;
        sunray_size_y -= 0.1;
    }

}

void mouse_callback(GLFWwindow *window, int button, int action, int mods){
    // TODO: Flip spin direction with mouse click
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && dir != 0){
        dir*=-1;
    } else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && dir == 0){
        dir = prev_dir*-1;
    }
}