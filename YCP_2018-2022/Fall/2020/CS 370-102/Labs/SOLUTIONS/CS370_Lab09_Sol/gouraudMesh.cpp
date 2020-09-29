#include <stdio.h>
#include <vector>
#include "vgl.h"
#include "objloader.h"
#include "utils.h"
#include "vmath.h"
#include "lighting.h"

using namespace vmath;
using namespace std;

enum VAO_IDs {Cube, Sphere, NumVAOs};
enum ObjBuffer_IDs {PosBuffer, NormBuffer, NumObjBuffers};
enum LightBuffer_IDs {LightBuffer, NumLightBuffers};
enum MaterialBuffer_IDs {MaterialBuffer, NumMaterialBuffers};
enum MaterialNames {Brass, RedPlastic};

GLuint VAOs[NumVAOs];
GLuint ObjBuffers[NumVAOs][NumObjBuffers];
GLuint LightBuffers[NumLightBuffers];
GLuint MaterialBuffers[NumMaterialBuffers];

GLint numVertices[NumVAOs];
GLint posCoords = 4;
GLint normCoords = 3;

const char *objFiles[NumVAOs] = {"../models/cube.obj", "../models/sphere.obj"};
// Camera
vec3 eye = {4.0f, 4.0f, 4.0f};
vec3 center = {0.0f, 0.0f, 0.0f};
vec3 up = {0.0f, 1.0f, 0.0f};

// Shader variables
GLuint program;
GLuint vPos;
GLuint vNorm;
GLuint camera_mat_loc;
GLuint model_mat_loc;
GLuint proj_mat_loc;
GLuint norm_mat_loc;
GLuint lights_block_idx;
GLuint materials_block_idx;
GLuint material_loc;
GLuint eye_loc;
const char *vertex_shader = "../gouraud.vert";
const char *frag_shader = "../gouraud.frag";

// Global state
mat4 proj_matrix;
mat4 model_matrix;
mat4 camera_matrix;
mat4 normal_matrix;
GLfloat cube_angle = 0.0;
GLdouble elTime = 0.0;
GLdouble rpm = 10.0;
vec3 axis = {0.0f, 1.0f, 0.0f};
vector<LightProperties> Lights;
vector<MaterialProperties> Materials;
GLuint MaterialIdx[NumVAOs] = {0, 1};

// Global screen dimensions
GLint ww,hh;

void build_geometry( );
void build_lights();
void build_materials();
void display( );
void render_scene( );
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, int button, int action, int mods);
void load_object(GLuint obj);
void draw_object(GLuint obj);

int main(int argc, char**argv)
{
	// Create OpenGL window
	GLFWwindow* window = CreateWindow("Gouraud Shading");
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    } else {
        printf("OpenGL window successfully created\n");
    }
    glfwGetFramebufferSize(window, &ww, &hh);
    // Register callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window,key_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);

	// Create geometry buffers
    build_geometry();
    // Create light buffers
    build_lights();
    // Create material buffers
    build_materials();
    
    // Load shaders
	ShaderInfo shaders[] = { {GL_VERTEX_SHADER, vertex_shader},{GL_FRAGMENT_SHADER, frag_shader},{GL_NONE, NULL} };
	program = LoadShaders(shaders);

	// Select shader program and associate shader variables
	vPos = glGetAttribLocation(program, "vPosition");
    vNorm = glGetAttribLocation(program, "vNormal");
    camera_mat_loc = glGetUniformLocation(program, "cam_matrix");
    model_mat_loc = glGetUniformLocation(program, "model_matrix");
    proj_mat_loc = glGetUniformLocation(program, "proj_matrix");
    norm_mat_loc = glGetUniformLocation(program, "norm_matrix");
    lights_block_idx = glGetUniformBlockIndex(program, "LightBuffer");
    materials_block_idx = glGetUniformBlockIndex(program, "MaterialBuffer");
    material_loc = glGetUniformLocation(program, "Material");
    eye_loc = glGetUniformLocation(program, "EyePosition");

    // Enable depth test
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
    // Generate vertex arrays for objects
    glGenVertexArrays(NumVAOs, VAOs);

    load_object(Cube);

    load_object(Sphere);
}

void build_lights( ) {
    // TODO: Create white light
    LightProperties whiteLight = {DIRECTIONAL, //type
                                  {0.0f, 0.0f, 0.0f}, //pad
                                  vec4(0.0f, 0.0f, 0.0f, 1.0f), //ambient
                                  vec4(1.0f, 1.0f, 1.0f, 1.0f), //diffuse
                                  vec4(1.0f, 1.0f, 1.0f, 1.0f), //specular
                                  vec4(0.0f, 0.0f, 0.0f, 1.0f),  //position
                                  vec3(-1.0f, -1.0f, -1.0f), //direction
                                  0.0f,       //pad2
                                  0.0f,   //cutoff
                                  0.0f,  //exponent
                                  {0.0f, 0.0f}  //pad3
    };

    // TODO: Add lights to Lights vector
    Lights.push_back(whiteLight);

    // Create uniform buffer for lights
    glGenBuffers(NumLightBuffers, LightBuffers);
    glBindBuffer(GL_UNIFORM_BUFFER, LightBuffers[LightBuffer]);
    glBufferData(GL_UNIFORM_BUFFER, Lights.size()*sizeof(LightProperties), Lights.data(), GL_STATIC_DRAW);
}

void build_materials( ) {
    // TODO: Create brass material
    MaterialProperties brass = {vec4(0.33f, 0.22f, 0.03f, 1.0f), //ambient
                                vec4(0.78f, 0.57f, 0.11f, 1.0f), //diffuse
                                vec4(0.99f, 0.91f, 0.81f, 1.0f), //specular
                                27.8f, //shininess
                                {0.0f, 0.0f, 0.0f}  //pad
    };

    // TODO: Create red plastic material
    MaterialProperties redPlastic = {vec4(0.3f, 0.0f, 0.0f, 1.0f), //ambient
                                     vec4(0.6f, 0.0f, 0.0f, 1.0f), //diffuse
                                     vec4(0.8f, 0.6f, 0.6f, 1.0f), //specular
                                     32.0f, //shininess
                                     {0.0f, 0.0f, 0.0f}  //pad
    };

    // TODO: Add materials to Materials vector
    Materials.push_back(brass);
    Materials.push_back(redPlastic);

    // Create uniform buffer for materials
    glGenBuffers(NumMaterialBuffers, MaterialBuffers);
    glBindBuffer(GL_UNIFORM_BUFFER, MaterialBuffers[MaterialBuffer]);
    glBufferData(GL_UNIFORM_BUFFER, Materials.size()*sizeof(MaterialProperties), Materials.data(), GL_STATIC_DRAW);
}

void display( )
{
    proj_matrix = mat4().identity();
    camera_matrix = mat4().identity();

	// Clear window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set projection matrix
    // Set orthographic viewing volume anisotropic
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
    proj_matrix = frustum(-1.0f*xratio, 1.0f*xratio, -1.0f*yratio, 1.0f*yratio, 1.0f, 100.0f);

    // Set camera matrix
    camera_matrix = lookat(eye, center, up);

    // Render objects
	render_scene();

	glFlush();
}

void render_scene( ) {
	mat4 scale_matrix;
	mat4 rot_matrix;
	mat4 trans_matrix;

	// Select shader program
	glUseProgram(program);
	// Pass projection matrix to shader
    glUniformMatrix4fv(proj_mat_loc, 1, GL_FALSE, proj_matrix);
    // Pass camera matrix to shader
    glUniformMatrix4fv(camera_mat_loc, 1, GL_FALSE, camera_matrix);

	// Bind lights
	glUniformBlockBinding(program, lights_block_idx, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, LightBuffers[LightBuffer], 0, Lights.size()*sizeof(LightProperties));
    // Bind materials
    glUniformBlockBinding(program, materials_block_idx, 1);
    glBindBufferRange(GL_UNIFORM_BUFFER, 1, MaterialBuffers[MaterialBuffer], 0, Materials.size()*sizeof(MaterialProperties));
    // Set eye position
    glUniform3fv(eye_loc, 1, eye);

    // Draw cube
    trans_matrix = translation(0.0f, 0.0f, 0.0f);
    rot_matrix = rotation(cube_angle, normalize(axis));
    scale_matrix = scale(1.5f, 0.5f, 1.5f);
    model_matrix = trans_matrix*rot_matrix*scale_matrix;
    // TODO: Compute normal matrix
    normal_matrix = model_matrix.inverse().transpose();
    // Pass model matrix, normal matrix, and material index to shader
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniformMatrix4fv(norm_mat_loc, 1, GL_FALSE, normal_matrix);
    glUniform1i(material_loc, MaterialIdx[Cube]);
    draw_object(Cube);


    // Draw sphere
    trans_matrix = translation(0.0f, 1.5f, 0.0f);
    rot_matrix = rotation(cube_angle, normalize(axis))*rotation(90.0f, 1.0f, 0.0f, 0.0f);
    scale_matrix = scale(1.0f, 1.0f, 1.0f);
    model_matrix = trans_matrix*rot_matrix*scale_matrix;
    // TODO: Compute normal matrix
    normal_matrix = model_matrix.inverse().transpose();
    // Pass model matrix, normal matrix, and material index to shader
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniformMatrix4fv(norm_mat_loc, 1, GL_FALSE, normal_matrix);
    glUniform1i(material_loc, MaterialIdx[Sphere]);
    draw_object(Sphere);
    
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Move hexagon with arrow keys
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }
}

void mouse_callback(GLFWwindow *window, int button, int action, int mods){

}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);

    ww = width;
    hh = height;
}

void load_object(GLuint obj) {
    vector<vec4> vertices;
    vector<vec2> uvCoords;
    vector<vec3> normals;

    loadOBJ(objFiles[obj], vertices, uvCoords, normals);
    numVertices[obj] = vertices.size();
    // Create and load object buffers
    glGenBuffers(NumObjBuffers, ObjBuffers[obj]);
    glBindVertexArray(VAOs[obj]);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[obj][PosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*posCoords*numVertices[obj], vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[obj][NormBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*normCoords*numVertices[obj], normals.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void draw_object(GLuint obj){
    glBindVertexArray(VAOs[obj]);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[obj][PosBuffer]);
    glVertexAttribPointer(vPos, posCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vPos);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[obj][NormBuffer]);
    glVertexAttribPointer(vNorm, normCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vNorm);
    glDrawArrays(GL_TRIANGLES, 0, numVertices[obj]);

}
