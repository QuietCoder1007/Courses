// CS370 Assignment 2 - Rollin Train
// Fall 2020

#include <stdio.h>
#include <vector>
#include "vgl.h"
#include "objloader.h"
#include "utils.h"
#include "vmath.h"
#include "RollinTrain.h"
#define DEG2RAD (M_PI/180.0)
#define RAD2DEG (180.0f/3.14159f)
// View modes
#define ORTHOGRAPHIC 0
#define PERSPECTIVE 1

// Component indices
#define X 0
#define Y 1
#define Z 2

using namespace vmath;
using namespace std;

enum VAO_IDs {Cube, Cylinder, Cone, Torus, Human, NumVAOs};
enum Buffer_IDs {CubePosBuffer, CubeColBuffer, CylinderPosBuffer, CylinderColBuffer, ConePosBuffer, ConeColBuffer, TorusPosBuffer, TorusColBuffer, NumBuffers};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

GLint numVertices[NumVAOs];
GLint posCoords = 4;

// Camera
vec3 eye = {2.0f, 2.0f, 2.0f};
vec3 center = {0.0f, 0.0f, 0.0f};
vec3 up = {0.0f, 1.0f, 0.0f};
mat4 trans_matrix_smoke = mat4().identity();

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
const char *models[NumVAOs] = {"../models/cube.obj", "../models/cylinder.obj", "../models/cone.obj", "../models/torus.obj", "../models/RUST_3d_Low1.obj"};
GLdouble elTime = 0.0;
GLdouble speed = (RAIL_LENGTH/2.0f);
vec3 train_pos = {0.0f, 0.0f, 0.0f};
GLboolean animate = false;
GLint train_dir = -1;
GLint train_brake = 0;
GLint smoke_rising_speed = 2.50f;

// Global spherical coord values
GLfloat hex_angle = 0.0;
GLfloat hex_z = 0.0;
GLfloat delta = 0.1;
GLfloat azimuth = 45.0f;
GLfloat daz = 2.0f;
GLfloat elevation = 54.7f;
GLfloat del = 2.0f;
GLfloat radius = 3.46f;
GLfloat dr = 0.1f;
GLfloat min_radius = 0.5f;

int proj = ORTHOGRAPHIC;
GLfloat wheel_ang = 0.0f;

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
	GLFWwindow* window = CreateWindow("Rollin Train");
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
    glfwSetKeyCallback(window,key_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);

	// Create geometry buffers
    build_geometry();
    
    // Load shaders and associate shader variables
	ShaderInfo shaders[] = { {GL_VERTEX_SHADER, vertex_shader},{GL_FRAGMENT_SHADER, frag_shader},{GL_NONE, NULL} };
	program = LoadShaders(shaders);
    vPos = glGetAttribLocation(program, "vPosition");
    vCol = glGetUniformLocation(program, "vColor");
    model_mat_loc = glGetUniformLocation(program, "model_matrix");
    proj_mat_loc = glGetUniformLocation(program, "proj_matrix");
    cam_mat_loc = glGetUniformLocation(program, "camera_matrix");

    // Enable depth test
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // Set background color
    glClearColor(1.0f,1.0f,1.0f,1.0f);

    // Set Initial camera position
    GLfloat x, y, z;
    x = (GLfloat)(radius*sin(azimuth*DEG2RAD)*sin(elevation*DEG2RAD));
    y = (GLfloat)(radius*cos(elevation*DEG2RAD));
    z = (GLfloat)(radius*cos(azimuth*DEG2RAD)*sin(elevation*DEG2RAD));
    eye = vec3(x, y, z);

    // Set initial time
    elTime = glfwGetTime();

    // Start loop
    while ( !glfwWindowShouldClose( window ) ) {
    	// Draw graphics
        display();
        // Update other events like input handling
        glfwPollEvents();

		// TODO: Add animation
        if (animate){
            smoke_rising_speed+=2.00f;
            if (smoke_rising_speed == 100.00f){
                smoke_rising_speed = 2.0f;
                animate = 0;
            }
        }

        // Swap buffer onto screen
        glfwSwapBuffers( window );
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

	// TODO: Load models
    // Bind Cube vertex array object
    glBindVertexArray(VAOs[Cube]);

    // Load cube model and store number of vertices
    loadOBJ(models[Cube], vertices, uvCoords, normals);
    numVertices[Cube] = vertices.size();

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[CubePosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*posCoords*numVertices[Cube], vertices.data(), GL_STATIC_DRAW);

    // Clear model vectors
    vertices.clear();
    uvCoords.clear();
    normals.clear();

    glBindVertexArray(VAOs[Cylinder]);

    loadOBJ(models[Cylinder], vertices, uvCoords, normals);
    numVertices[Cylinder] = vertices.size();

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[CylinderPosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*posCoords*numVertices[Cylinder], vertices.data(), GL_STATIC_DRAW);

    // Clear model vectors
    vertices.clear();
    uvCoords.clear();
    normals.clear();

    glBindVertexArray(VAOs[Cone]);

    loadOBJ(models[Cone], vertices, uvCoords, normals);
    numVertices[Cone] = vertices.size();

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ConePosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*posCoords*numVertices[Cone], vertices.data(), GL_STATIC_DRAW);

    // Clear model vectors
    vertices.clear();
    uvCoords.clear();
    normals.clear();

    glBindVertexArray(VAOs[Torus]);

    loadOBJ(models[Torus], vertices, uvCoords, normals);
    numVertices[Torus] = vertices.size();

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[TorusPosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*posCoords*numVertices[Torus], vertices.data(), GL_STATIC_DRAW);
}

void display( )
{
    // Declare projection and camera matrices
    mat4 proj_matrix = mat4().identity();
    mat4 camera_matrix = mat4().identity();

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

    // TODO: Set projection and camera matrices
    proj_matrix = frustum(-1.00f*xratio, 1.00f*xratio, -1.00f*yratio, 1.00f*yratio, 1.00f, 64.00f);

    // Pass projection matrix to shader
    glUniformMatrix4fv(proj_mat_loc, 1, GL_FALSE, proj_matrix);

    // TODO: Set camera matrix
    camera_matrix = lookat(eye, center, up);

    // Pass camera matrix to shader
    glUniformMatrix4fv(cam_mat_loc, 1, GL_FALSE, camera_matrix);

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

    // TODO: Draw geometry
    // Set cube transformation matrix -- Train Body
    trans_matrix = translate(BODY_X, BODY_Y - 0.50f, BODY_Z+(hex_z*train_brake));
    rot_matrix = rotate(00.00f, 1.00f, 0.00f, 0.00f);
    scale_matrix = scale(BODY_WIDTH, BODY_HEIGHT, BODY_LENGTH);
    model_matrix = trans_matrix * rot_matrix * scale_matrix;
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniform4fv(vCol, 1, body_color);

    draw_obj(VAOs[Cube], Buffers[CubePosBuffer], numVertices[Cube]);

    // Set cube transformation matrix -- Engineer's Compartment
    trans_matrix = translate(ENG_X, ENG_Y - 0.50f, ENG_Z+(hex_z*train_brake));
    rot_matrix = rotate(0.00f, 0.00f, 0.00f, 0.00f);
    scale_matrix = scale(ENG_WIDTH, ENG_HEIGHT, ENG_LENGTH);
    model_matrix = trans_matrix * rot_matrix * scale_matrix;
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniform4fv(vCol, 1, eng_color);

    draw_obj(VAOs[Cube], Buffers[CubePosBuffer], numVertices[Cube]);

    // Set cube transformation matrix -- Left Rail tie
    trans_matrix = translate(RAIL_TIES_OFFSET_X - 0.7f, RAIL_OFFSET_Y, RAIL_OFFSET_Z);
    rot_matrix = rotate(00.00f, 1.00f, 0.00f, 0.00f);
    scale_matrix = scale(RAIL_WIDTH, RAIL_HEIGHT, RAIL_LENGTH);
    model_matrix = trans_matrix * rot_matrix * scale_matrix;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniform4fv(vCol, 1, rail_color);

    draw_obj(VAOs[Cube], Buffers[CubePosBuffer], numVertices[Cube]);

    // Set cube transformation matrix -- Right Rail track
    trans_matrix = translate(RAIL_OFFSET_X, RAIL_OFFSET_Y, RAIL_OFFSET_Z);
    rot_matrix = rotate(00.00f, 1.00f, 0.00f, 0.00f);
    scale_matrix = scale(RAIL_WIDTH, RAIL_HEIGHT, RAIL_LENGTH);
    model_matrix = trans_matrix * rot_matrix * scale_matrix;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniform4fv(vCol, 1, rail_color);

    draw_obj(VAOs[Cube], Buffers[CubePosBuffer], numVertices[Cube]);

    // Set cube transformation matrix -- Rail Ties
    int total_rails = 20;

    for (int i = 0; i < total_rails; ++i) {
        trans_matrix = translate(RAIL_TIES_OFFSET_X, RAIL_TIES_OFFSET_Y + 0.10f,
                                 RAIL_LENGTH - 2 * ((RAIL_LENGTH / total_rails) * i));
        rot_matrix = rotate(90.00f, 0.00f, 1.00f, 0.00f);
        scale_matrix = scale(RAIL_TIES_WIDTH, RAIL_TIES_HEIGHT, RAIL_TIES_LENGTH * 0.4f);
        model_matrix = trans_matrix * rot_matrix * scale_matrix;

        glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
        glUniform4fv(vCol, 1, ties_color);

        draw_obj(VAOs[Cube], Buffers[CubePosBuffer], numVertices[Cube]);
    }

    // Set cube transformation matrix --- BOTTOM BLOCK
    trans_matrix = translate(0.00f, 2.00f, -RAIL_LENGTH - 5.00f);
    rot_matrix = rotate(90.00f, 0.00f, 1.00f, 0.00f);
    scale_matrix = scale(BOTTOM_BLOCK_SIZE, BOTTOM_BLOCK_SIZE, BOTTOM_BLOCK_SIZE);
    model_matrix = trans_matrix * rot_matrix * scale_matrix;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniform4fv(vCol, 1, bottom_color);

    draw_obj(VAOs[Cube], Buffers[CubePosBuffer], numVertices[Cube]);

    // Set cube transformation matrix --- MIDDLE BLOCK
    trans_matrix = translate(0.00f, 4.00f, -RAIL_LENGTH - 5.00f);
    rot_matrix = rotate(90.00f, 0.00f, 1.00f, 0.00f);
    scale_matrix = scale(MIDDLE_BLOCK_SIZE, MIDDLE_BLOCK_SIZE, MIDDLE_BLOCK_SIZE);
    model_matrix = trans_matrix * rot_matrix * scale_matrix;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniform4fv(vCol, 1, middle_color);

    draw_obj(VAOs[Cube], Buffers[CubePosBuffer], numVertices[Cube]);

    // Set cube transformation matrix --- TOP BLOCK
    trans_matrix = translate(0.00f, 5.50f, -RAIL_LENGTH - 5.00f);
    rot_matrix = rotate(90.00f, 0.00f, 1.00f, 0.00f);
    scale_matrix = scale(TOP_BLOCK_SIZE, TOP_BLOCK_SIZE, TOP_BLOCK_SIZE);
    model_matrix = trans_matrix * rot_matrix * scale_matrix;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniform4fv(vCol, 1, top_color);

    draw_obj(VAOs[Cube], Buffers[CubePosBuffer], numVertices[Cube]);

    // Set cube transformation matrix --- Engine Smoke
    trans_matrix_smoke = translate(STACK_X, (2*STACK_Y)+smoke_rising_speed, STACK_Z+(hex_z*train_brake));
    rot_matrix = rotate(90.00f, 0.00f, 1.00f, 0.00f);
    scale_matrix = scale(STACK_RADIUS, STACK_HEIGHT, STACK_RADIUS);
    model_matrix = trans_matrix * rot_matrix * scale_matrix;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniform4fv(vCol, 1, smoke_color);

    draw_obj(VAOs[Cylinder], Buffers[CylinderPosBuffer], numVertices[Cylinder]);

    // Set cube transformation matrix --- Engine Funnel Body
    trans_matrix = translate(STACK_X, STACK_Y, STACK_Z+(hex_z*train_brake));
    rot_matrix = rotate(90.00f, 0.00f, 1.00f, 0.00f);
    scale_matrix = scale(STACK_RADIUS, STACK_HEIGHT, STACK_RADIUS);
    model_matrix = trans_matrix * rot_matrix * scale_matrix;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniform4fv(vCol, 1, stack_color);

    draw_obj(VAOs[Cylinder], Buffers[CylinderPosBuffer], numVertices[Cylinder]);

    // Set cube transformation matrix --- Engine Funnel
    trans_matrix = translate(STACK_X, STACK_Y, STACK_Z+(hex_z*train_brake));
    rot_matrix = rotate(180.00f, 0.00f, 0.00f, 1.00f);
    scale_matrix = scale(FUNNEL_RADIUS, FUNNEL_HEIGHT, FUNNEL_RADIUS);
    model_matrix = trans_matrix * rot_matrix * scale_matrix;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniform4fv(vCol, 1, stack_color);

    draw_obj(VAOs[Cone], Buffers[ConePosBuffer], numVertices[Cone]);

    int total_wheels = 6;
    int total_spokes = total_wheels*2;

    // Wheels for loop
    for (int i = 0; i < total_wheels / 2; ++i) {

        switch (i % 3) {
            case 0:
                trans_matrix = translate(WHEEL_X, WHEEL_Y, WHEEL_Z+(hex_z*train_brake));
                break;
            case 1:
                trans_matrix = translate(WHEEL_X, WHEEL_Y, (WHEEL_Z * 0.00f)+(hex_z*train_brake));
                break;
            case 2:
                trans_matrix = translate(WHEEL_X, WHEEL_Y, -WHEEL_Z+(hex_z*train_brake));
                break;
        }

        rot_matrix = rotate(90.00f, 0.00f, 0.00f, 1.00f);
        scale_matrix = scale(WHEEL_RADIUS, WHEEL_WIDTH, WHEEL_RADIUS);
        model_matrix = trans_matrix * rot_matrix * scale_matrix;

        glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
        glUniform4fv(vCol, 1, wheel_color);

        draw_obj(VAOs[Torus], Buffers[TorusPosBuffer], numVertices[Torus]);

        switch (i % 3) {
            case 0:
                trans_matrix = translate(-WHEEL_X, WHEEL_Y, WHEEL_Z+(hex_z*train_brake));
                break;
            case 1:
                trans_matrix = translate(-WHEEL_X, WHEEL_Y, (WHEEL_Z * 0.00f)+(hex_z*train_brake));
                break;
            case 2:
                trans_matrix = translate(-WHEEL_X, WHEEL_Y, -WHEEL_Z+(hex_z*train_brake));
                break;
        }

        rot_matrix = rotate(90.00f, 0.00f, 0.00f, 1.00f);
        scale_matrix = scale(WHEEL_RADIUS, WHEEL_WIDTH, WHEEL_RADIUS);
        model_matrix = trans_matrix * rot_matrix * scale_matrix;

        glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
        glUniform4fv(vCol, 1, wheel_color);

        draw_obj(VAOs[Torus], Buffers[TorusPosBuffer], numVertices[Torus]);
    }

    // Spokes for loop
    for (int i = 0; i < total_wheels; ++i) {
        switch (i % 6) {
            case 0:
                trans_matrix = translate(WHEEL_X, WHEEL_Y, WHEEL_Z+(hex_z*train_brake));
                break;
            case 1:
                trans_matrix = translate(WHEEL_X, WHEEL_Y, (WHEEL_Z * 0.00f)+(hex_z*train_brake));
                break;
            case 2:
                trans_matrix = translate(WHEEL_X, WHEEL_Y, -WHEEL_Z+(hex_z*train_brake));
                break;
            case 3:
                trans_matrix = translate(-WHEEL_X, WHEEL_Y, (WHEEL_Z * 0.00f)+(hex_z*train_brake));
                break;
            case 4:
                trans_matrix = translate(-WHEEL_X, WHEEL_Y, WHEEL_Z+(hex_z*train_brake));
                break;
            case 5:
                trans_matrix = translate(-WHEEL_X, WHEEL_Y, -WHEEL_Z+(hex_z*train_brake));
                break;
        }
        for (int j = 0; j < total_spokes; ++j) {
            // Set cube transformation matrix --- Back Right Wheel
            rot_matrix = rotate((360.00f/total_spokes) * j, 1.00f, 0.00f, 0.00f);
            scale_matrix = scale(SPOKE_WIDTH, SPOKE_LENGTH, SPOKE_WIDTH);
            model_matrix = trans_matrix * rot_matrix * scale_matrix;

            glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
            glUniform4fv(vCol, 1, wheel_color);

            draw_obj(VAOs[Cylinder], Buffers[CylinderPosBuffer], numVertices[Cylinder]);

        }
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // ESC to quit
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }

	// TODO: Add keypress functionality
    // Adjust azimuth
    if (key == GLFW_KEY_A) {

        if (azimuth > 360.0) {
            azimuth -= 360.0;
        }
        else
        {
            azimuth += daz;
        }
    } else if (key == GLFW_KEY_D) {

        if (azimuth < 0.0)
        {
            azimuth += 360.0;
        }
        else
        {
            azimuth -= daz;
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

    // TODO: Turn on brake
    if (key == GLFW_KEY_SPACE && train_brake == 0 && action == GLFW_RELEASE){
        train_brake = 1;
    } else if (key == GLFW_KEY_SPACE && train_brake == 1 && action == GLFW_RELEASE){
        train_brake = 0;
    }

    // TODO: Move train with arrow keys
    if (key == GLFW_KEY_UP && train_brake == 1) {
        hex_z -= delta;
    } else if (key == GLFW_KEY_DOWN && train_brake == 1) {
        hex_z += delta;
    }
}

void mouse_callback(GLFWwindow *window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        animate = true;
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);

    ww = width;
    hh = height;
}

void draw_obj(GLuint VAO, GLuint Buffer, int numVert) {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, Buffer);
    glVertexAttribPointer(vPos, posCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vPos);
    glDrawArrays(GL_TRIANGLES, 0, numVert);
}
