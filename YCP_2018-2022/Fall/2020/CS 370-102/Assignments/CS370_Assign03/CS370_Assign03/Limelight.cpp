// CS370 Assignment 3 - LimeLight
// Fall 2020

#include <stdio.h>
#include <vector>
#include "vgl.h"
#include "objloader.h"
#include "utils.h"
#include "vmath.h"
#include "lighting.h"

using namespace vmath;
using namespace std;

enum VAO_IDs {Cube, Sphere, Octahedron, Circle, Cylinder, Donut, NumVAOs};
enum ObjBuffer_IDs {PosBuffer, NormBuffer, NumObjBuffers};
enum LightBuffer_IDs {LightBuffer, NumLightBuffers};
enum MaterialBuffer_IDs {MaterialBuffer, NumMaterialBuffers};
enum MaterialNames {Brass, RedPlastic, WhitePlastic, Wood};

GLuint VAOs[NumVAOs];
GLuint ObjBuffers[NumVAOs][NumObjBuffers];
GLuint LightBuffers[NumLightBuffers];
GLuint MaterialBuffers[NumMaterialBuffers];

GLint numVertices[NumVAOs];
GLint posCoords = 4;
GLint normCoords = 3;

const char *objFiles[NumVAOs] = {"../models/cube.obj", "../models/sphere.obj", "../models/octahedron.obj", "../models/half_circle.obj", "../models/cylinder.obj", "../models/donut.obj"};
// Camera
vec3 eye = {1.0f, 1.0f, 1.0f};
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
GLuint num_lights_loc;
GLuint eye_loc;
GLuint light_on_loc;
const char *vertex_shader = "../phong.vert";
const char *frag_shader = "../phong.frag";

// Global state
mat4 proj_matrix;
mat4 model_matrix;
mat4 camera_matrix;
mat4 normal_matrix;
GLfloat cube_angle = 0.0;
GLdouble elTime = 0.0;
GLdouble rpm = 0.0;
GLfloat movement_speed = 0.0f;
GLfloat bounce_speed = 1.50f;
vec3 axis = {0.0f, 1.0f, 0.0f};
vector<LightProperties> Lights;
vector<MaterialProperties> Materials;
GLint MaterialIdx[NumVAOs] = {Brass, RedPlastic, WhitePlastic, Wood};
GLuint numLights;
GLint lightOn[8] = {0,0,0,0,0,0,0,0};
GLboolean sphere_bounce = false;
GLboolean b_up = false;
GLboolean b_down = false;
GLboolean octa_spin = false;
GLboolean cube_move = false;
GLboolean m_back = true;
GLboolean m_forth = false;
GLfloat cube_spd = 0.1;
GLfloat sphere_spd = 0.1;

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
    GLFWwindow* window = CreateWindow("Phong Shading");
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
    num_lights_loc = glGetUniformLocation(program, "NumLights");
    eye_loc = glGetUniformLocation(program, "EyePosition");
    light_on_loc = glGetUniformLocation(program, "LightOn");

    // Enable depth test
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

    // Start loop
    while ( !glfwWindowShouldClose( window ) ) {
        // Draw graphics
        display();
        // Update other events like input handling
        glfwPollEvents();

        // TODO: Add animation
        if (octa_spin){
            rpm = 20.00;
        } else {
            rpm = 0.00;
        }

        GLdouble curTime = glfwGetTime();
        cube_angle += (curTime-elTime)*(rpm/60.0)*360.0;
        elTime = curTime;

        if (sphere_bounce){
            if(b_up && movement_speed < 30.50f){
                movement_speed += sphere_spd;
            }else if(m_forth && movement_speed >= 30.50f) {
                b_up = false;
                b_down = true;
            }

            if(b_down && movement_speed >= 1.50f){
                movement_speed -= sphere_spd;
            }else if(b_down && movement_speed < 1.50f) {
                b_up = true;
                b_down = false;
            }
        }  else {
            sphere_spd = 0.0f;
        }

        if (cube_move){
            if(m_forth && movement_speed < 2.00f){
                movement_speed += cube_spd;
            }else if(m_forth && movement_speed >= 2.00f) {
                m_forth = false;
                m_back = true;
            }

            if(m_back && movement_speed >= 0.00f){
                movement_speed -= cube_spd;
            }else if(m_back && movement_speed < 0.00f) {
                m_forth = true;
                m_back = false;
            }
        } else {
            cube_spd = 0.0f;
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
    // Generate vertex arrays for objects
    glGenVertexArrays(NumVAOs, VAOs);

    load_object(Cube);
    
    // TODO: Load additional models
    load_object(Sphere);
    load_object(Octahedron);
    load_object(Circle);
    load_object(Cylinder);
    load_object(Donut);
}

void build_lights( ) {
	// TODO: Create lights
    LightProperties whitePointLight = {POINT, //type
                                       {0.0f, 0.0f, 0.0f}, //pad
                                       vec4(0.0f, 0.0f, 0.0f, 1.0f), //ambient
                                       vec4(1.0f, 1.0f, 1.0f, 1.0f), //diffuse
                                       vec4(1.0f, 1.0f, 1.0f, 1.0f), //specular
                                       vec4(0.0f, 5.0f, 0.0f, 1.0f),  //position
                                       vec3(0.0f, -1.0f, 0.0f), //direction
                                       0.0f,       //pad2
                                       0.0f,   //cutoff
                                       0.0f,  //exponent
                                       {0.0f, 0.0f}  //pad3
    };

    LightProperties redSpotLight = {SPOT, //type
                                    {0.0f, 0.0f, 0.0f}, //pad
                                    vec4(0.0f, 0.0f, 0.0f, 1.0f), //ambient
                                    vec4(1.0f, 0.0f, 0.0f, 1.0f), //diffuse
                                    vec4(1.0f, 1.0f, 1.0f, 1.0f), //specular
                                    vec4(10.0f, 10.0f, 0.0f, 1.0f),  //position
                                    vec3(0.0f, -1.0f, 0.0f), //direction
                                    0.0f,       //pad2
                                    30.0f,   //cutoff
                                    0.0f,  //exponent
                                    {0.0f, 0.0f}  //pad3
    };

    LightProperties greenSpotLight = {SPOT, //type
                                      {0.0f, 0.0f, 0.0f}, //pad
                                      vec4(0.0f, 0.0f, 0.0f, 1.0f), //ambient
                                      vec4(0.0f, 1.0f, 0.0f, 1.0f), //diffuse
                                      vec4(1.0f, 1.0f, 1.0f, 1.0f), //specular
                                      vec4(0.0f, 10.0f, 0.0f, 1.0f),  //position
                                      vec3(0.0f, -1.0f, 0.0f), //direction
                                      0.0f,       //pad2
                                      30.0f,   //cutoff
                                      0.0f,  //exponent
                                      {0.0f, 0.0f}  //pad3
    };


    LightProperties blueSpotLight = {SPOT, //type
                                      {0.0f, 0.0f, 0.0f}, //pad
                                      vec4(0.0f, 0.0f, 0.0f, 1.0f), //ambient
                                      vec4(0.0f, 0.0f, 1.0f, 1.0f), //diffuse
                                      vec4(1.0f, 1.0f, 1.0f, 1.0f), //specular
                                      vec4(-10.0f, 10.0f, 0.0f, 1.0f),  //position
                                      vec3(0.0f, -1.0f, 0.0f), //direction
                                      0.0f,       //pad2
                                      30.0f,   //cutoff
                                      0.0f,  //exponent
                                      {0.0f, 0.0f}  //pad3
    };

    Lights.push_back(whitePointLight);
    Lights.push_back(greenSpotLight);
    Lights.push_back(redSpotLight);
    Lights.push_back(blueSpotLight);
    numLights = Lights.size();

    // Create uniform buffer for lights
    glGenBuffers(NumLightBuffers, LightBuffers);
    glBindBuffer(GL_UNIFORM_BUFFER, LightBuffers[LightBuffer]);
    glBufferData(GL_UNIFORM_BUFFER, Lights.size()*sizeof(LightProperties), Lights.data(), GL_STATIC_DRAW);
}

void build_materials( ) {
	// TODO: Create materials
	// Create brass material
	MaterialProperties brass = {vec4(0.33f, 0.22f, 0.03f, 1.0f), //ambient
                                vec4(0.78f, 0.57f, 0.11f, 1.0f), //diffuse
                                vec4(0.99f, 0.91f, 0.81f, 1.0f), //specular
                                27.8f, //shininess
                                {0.0f, 0.0f, 0.0f}  //pad
    };

    // Create red plastic material
    MaterialProperties redPlastic = {vec4(0.3f, 0.0f, 0.0f, 1.0f), //ambient
                                     vec4(0.6f, 0.0f, 0.0f, 1.0f), //diffuse
                                     vec4(0.8f, 0.6f, 0.6f, 1.0f), //specular
                                     32.0f, //shininess
                                     {0.0f, 0.0f, 0.0f}  //pad
    };

    // Create white plastic material
    MaterialProperties whitePlastic = {vec4(1.0f, 1.0f, 1.0f, 1.0f), //ambient
                                       vec4(1.0f, 1.0f, 1.0f, 1.0f), //diffuse
                                       vec4(1.0f, 1.0f, 1.0f, 1.0f), //specular
                                       32.0f, //shininess
                                       {0.0f, 0.0f, 0.0f}  //pad
    };

    // Create wood material
    MaterialProperties wood = {vec4(1.0f, 0.92f, 0.80f, 1.0f), //ambient
                                     vec4(0.4f, 0.4f, 0.4f, 1.0f), //diffuse
                                     vec4(0.8f, 0.6f, 0.6f, 1.0f), //specular
                                     32.0f, //shininess
                                     {0.0f, 0.0f, 0.0f}  //pad
    };

    // Add materials to Materials vector
    Materials.push_back(brass);
    Materials.push_back(redPlastic);
    Materials.push_back(whitePlastic);
    Materials.push_back(wood);

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
    proj_matrix = ortho(-10.0f*xratio, 10.0f*xratio, -10.0f*yratio, 10.0f*yratio, -10.0f, 10.0f);

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
    // Set num lights
    glUniform1i(num_lights_loc, numLights);
    glUniform1iv(light_on_loc, numLights, lightOn);

    // TODO: Render objects
    // Draw semi-circle
    trans_matrix = translation(0.00f, 0.00f, -2.00f);
    rot_matrix = rotation(180.0f, normalize(axis));
    scale_matrix = scale(9.0f, 1.0f, 10.0f);
    model_matrix = trans_matrix*rot_matrix*scale_matrix;
    // Compute normal matrix
    normal_matrix = model_matrix.inverse().transpose();
    // Pass model matrix, normal matrix, and material index to shader
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniformMatrix4fv(norm_mat_loc, 1, GL_FALSE, normal_matrix);
    glUniform1i(material_loc, MaterialIdx[Circle]);
    draw_object(Circle);

    // Draw octahedron
    trans_matrix = translation(-10.0f, 1.00f, 0.0f);
    rot_matrix = rotation(cube_angle, normalize(axis))*rotation(90.0f, 1.0f, 0.0f, 0.0f);
    scale_matrix = scale(1.0f, 1.0f, 1.0f);
    model_matrix = trans_matrix*rot_matrix*scale_matrix;
    // Compute normal matrix
    normal_matrix = model_matrix.inverse().transpose();
    // Pass model matrix, normal matrix, and material index to shader
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniformMatrix4fv(norm_mat_loc, 1, GL_FALSE, normal_matrix);
    glUniform1i(material_loc, MaterialIdx[Octahedron]);
    draw_object(Octahedron);

    // Draw cube
    trans_matrix = translation(0.0f, 1.5f, movement_speed);
    rot_matrix = rotation(90.00f, axis);
    scale_matrix = scale(1.0f, 1.0f, 1.0f);
    model_matrix = trans_matrix*rot_matrix*scale_matrix;
    // Compute normal matrix
    normal_matrix = model_matrix.inverse().transpose();
    // Pass model matrix, normal matrix, and material index to shader
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniformMatrix4fv(norm_mat_loc, 1, GL_FALSE, normal_matrix);
    glUniform1i(material_loc, MaterialIdx[Cube]);
    draw_object(Cube);

    // Draw sphere
    trans_matrix = translation(10.0f, bounce_speed, 0.0f);
    rot_matrix = rotation(90.00f, axis);
    scale_matrix = scale(1.5f, 1.5f, 1.5f);
    model_matrix = trans_matrix*rot_matrix*scale_matrix;
    // Compute normal matrix
    normal_matrix = model_matrix.inverse().transpose();
    // Pass model matrix, normal matrix, and material index to shader
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniformMatrix4fv(norm_mat_loc, 1, GL_FALSE, normal_matrix);
    glUniform1i(material_loc, MaterialIdx[Brass]);
    draw_object(Sphere);

    // Draw cylinder
    trans_matrix = translation(5.0f, -1.5f, 0.0f);
    rot_matrix = rotation(90.0f, 1.0f, 0.0f, 0.0f);
    scale_matrix = scale(1.0f, 1.0f, 1.0f);
    model_matrix = trans_matrix*rot_matrix*scale_matrix;
    // Compute normal matrix
    normal_matrix = model_matrix.inverse().transpose();
    // Pass model matrix, normal matrix, and material index to shader
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniformMatrix4fv(norm_mat_loc, 1, GL_FALSE, normal_matrix);
    glUniform1i(material_loc, MaterialIdx[WhitePlastic]);
    draw_object(Cylinder);

    // Draw donut
    trans_matrix = translation(5.0f, -1.5f, 0.0f);
    rot_matrix = rotation(90.0f, 1.0f, 0.0f, 0.0f);
    scale_matrix = scale(1.0f, 1.0f, 1.0f);
    model_matrix = trans_matrix*rot_matrix*scale_matrix;
    // Compute normal matrix
    normal_matrix = model_matrix.inverse().transpose();
    // Pass model matrix, normal matrix, and material index to shader
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glUniformMatrix4fv(norm_mat_loc, 1, GL_FALSE, normal_matrix);
    glUniform1i(material_loc, MaterialIdx[Brass]);
    draw_object(Donut);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Esc exits program
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }

    // TODO: Toggle spotlights (lightOn[])
    // All lights on
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
        for (int i = 0; i < numLights; ++i) {
            if(lightOn[i] == 1){
                lightOn[i] = 0;
            } else {
                lightOn[i] = 1;
            }
        }
    }

    if (key == GLFW_KEY_1 && action == GLFW_RELEASE) {
        if(lightOn[0] == 1){
                lightOn[0] = 0;
            } else {
                lightOn[0] = 1;
            }
    }

    if (key == GLFW_KEY_2 && action == GLFW_RELEASE) {
        if(lightOn[1] == 1){
                lightOn[1] = 0;
            } else {
                lightOn[1] = 1;
            }
    }

    if (key == GLFW_KEY_3 && action == GLFW_RELEASE) {
        if(lightOn[2] == 1){
                lightOn[2] = 0;
        } else {
                lightOn[2] = 1;
        }
    }

    if (key == GLFW_KEY_4 && action == GLFW_RELEASE) {
        if(lightOn[3] == 1){
                lightOn[3] = 0;
            } else {
                lightOn[3] = 1;
            }
    }

    // Cube move back and forth
    if (key == GLFW_KEY_V && !cube_move && action == GLFW_RELEASE) {
        cube_move = true;
    } else if (key == GLFW_KEY_V && cube_move && action == GLFW_RELEASE) {
        cube_move = false;
    }

    // Sphere bounces up and down
    if (key == GLFW_KEY_B && !sphere_bounce && action == GLFW_RELEASE) {
        sphere_bounce = true;
    } else if (key == GLFW_KEY_B && sphere_bounce && action == GLFW_RELEASE) {
        sphere_bounce = false;
    }

    // Octahedron spins
    if (key == GLFW_KEY_N && !octa_spin && action == GLFW_RELEASE) {
        octa_spin = true;
    } else if (key == GLFW_KEY_N && octa_spin && action == GLFW_RELEASE) {
        octa_spin = false;
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
