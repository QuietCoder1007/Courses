// CS370 Assignment 4 - Walking Man
// Fall 2020

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"	// Sean Barrett's image loader - http://nothings.org/
#include <stdio.h>
#include <vector>
#include "vgl.h"
#include "objloader.h"
#include "utils.h"
#include "vmath.h"
#include "lighting.h"
#include "MatNode.h"
#include "TexNode.h"
#include "player.h"
#define DEG2RAD (M_PI/180.0)

using namespace vmath;
using namespace std;

enum VAO_IDs {Cube, Sphere, TexCube, Background, NumVAOs};
enum ObjBuffer_IDs {PosBuffer, NormBuffer, TexBuffer, NumObjBuffers};
enum LightBuffer_IDs {LightBuffer, NumLightBuffers};
enum MaterialBuffer_IDs {MaterialBuffer, NumMaterialBuffers};
enum MaterialNames {Skin};
enum Textures {YCP, Shirt, Face, Basketball, Wood, NumTextures};

GLuint VAOs[NumVAOs];
GLuint ObjBuffers[NumVAOs][NumObjBuffers];
GLuint LightBuffers[NumLightBuffers];
GLuint MaterialBuffers[NumMaterialBuffers];
GLuint TextureIDs[NumTextures];

GLint numVertices[NumVAOs];
GLint posCoords = 4;
GLint normCoords = 3;
GLint texCoords = 2;

vector<const char *> objFiles = {"../models/cube.obj", "../models/uv_sphere.obj"};
vector<const char *> texFiles = {"../textures/ycp.png", "../textures/shirt_z.png", "../textures/face.png", "../textures/bball.png", "../textures/wood.png"};
// Camera
vec3 eye = {4.0f, 4.0f, 4.0f};
vec3 center = {0.0f, 0.0f, 0.0f};
vec3 up = {0.0f, 1.0f, 0.0f};

// Lighting Shader variables
GLuint light_program;
GLuint light_vPos;
GLuint light_vNorm;
GLuint light_camera_mat_loc;
GLuint light_model_mat_loc;
GLuint light_proj_mat_loc;
GLuint light_norm_mat_loc;
GLuint lights_block_idx;
GLuint materials_block_idx;
GLuint num_lights_loc;
GLuint material_loc;
GLuint light_eye_loc;
const char *light_vertex_shader = "../phong.vert";
const char *light_frag_shader = "../phong.frag";

// Texture Shader variables
GLuint tex_program;
GLuint tex_vPos;
GLuint tex_vTex;
GLuint tex_camera_mat_loc;
GLuint tex_model_mat_loc;
GLuint tex_proj_mat_loc;
const char *tex_vertex_shader = "../basicTex.vert";
const char *tex_frag_shader = "../basicTex.frag";

// Global state
mat4 proj_matrix;
mat4 model_matrix;
mat4 camera_matrix;
vector<LightProperties> Lights;
vector<MaterialProperties> Materials;
GLuint numLights;

// Scene graph nodes
TexNode base;
TexNode torso;
MatNode left_upper_arm;
MatNode right_upper_arm;
MatNode left_lower_arm;
MatNode right_lower_arm;
MatNode left_upper_leg;
//MatNode left_lower_leg;
MatNode right_upper_leg;
//MatNode right_lower_leg;
//TexNode bball;


// Elapsed time
GLdouble elTime = 0.0;


// Animation variables
GLboolean animate = false;

// Global spherical coord values
GLfloat azimuth = 45.0f;
GLfloat daz = 2.0f;
GLfloat elevation = 54.7f;
GLfloat del = 2.0f;
GLfloat radius = 5.0f;

// Global screen dimensions
GLint ww,hh;

void build_geometry( );
void build_lights( );
void build_materials( );
void build_textures();
void build_scene_graph( );
void display( );
void render_scene( );
void traverse_scene_graph(BaseNode *node, mat4 baseTransform);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, int button, int action, int mods);
void load_object(GLuint obj);
void draw_object(GLuint obj);
void draw_background();
void update_scene_graph(GLdouble dT);

int main(int argc, char**argv)
{
	// Create OpenGL window
	GLFWwindow* window = CreateWindow("Go Spartans!");
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

    // Load light shaders
	ShaderInfo light_shaders[] = { {GL_VERTEX_SHADER, light_vertex_shader},{GL_FRAGMENT_SHADER, light_frag_shader},{GL_NONE, NULL} };
	light_program = LoadShaders(light_shaders);

	// Select shader program and associate shader variables
	light_vPos = glGetAttribLocation(light_program, "vPosition");
    light_vNorm = glGetAttribLocation(light_program, "vNormal");
    light_camera_mat_loc = glGetUniformLocation(light_program, "cam_matrix");
    light_model_mat_loc = glGetUniformLocation(light_program, "model_matrix");
    light_proj_mat_loc = glGetUniformLocation(light_program, "proj_matrix");
    light_norm_mat_loc = glGetUniformLocation(light_program, "norm_matrix");
    lights_block_idx = glGetUniformBlockIndex(light_program, "LightBuffer");
    num_lights_loc = glGetUniformLocation(light_program, "NumLights");
    materials_block_idx = glGetUniformBlockIndex(light_program, "MaterialBuffer");
    material_loc = glGetUniformLocation(light_program, "Material");
    light_eye_loc = glGetUniformLocation(light_program, "EyePosition");

    // Load texture shaders
    ShaderInfo tex_shaders[] = { {GL_VERTEX_SHADER, tex_vertex_shader},{GL_FRAGMENT_SHADER, tex_frag_shader},{GL_NONE, NULL} };
    tex_program = LoadShaders(tex_shaders);

    // Select shader program and associate shader variables
    tex_vPos = glGetAttribLocation(tex_program, "vPosition");
    tex_vTex = glGetAttribLocation(tex_program, "vTexCoord");
    tex_camera_mat_loc = glGetUniformLocation(tex_program, "cam_matrix");
    tex_model_mat_loc = glGetUniformLocation(tex_program, "model_matrix");
    tex_proj_mat_loc = glGetUniformLocation(tex_program, "proj_matrix");

    // Create geometry buffers
    build_geometry();
    // Create light buffers
    build_lights();
    // Create material buffers
    build_materials();
    // Create textures
    build_textures();
    // Create scene graph
    build_scene_graph();

    // Enable depth test
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set initial camera position
    GLfloat x, y, z;
    x = (GLfloat)(radius*sin(azimuth*DEG2RAD)*sin(elevation*DEG2RAD));
    y = (GLfloat)(radius*cos(elevation*DEG2RAD));
    z = (GLfloat)(radius*cos(azimuth*DEG2RAD)*sin(elevation*DEG2RAD));
    eye = vec3(x, y, z);

    // Start loop
    while ( !glfwWindowShouldClose( window ) ) {
    	// Draw graphics
        display();
        // Update other events like input handling
        glfwPollEvents();
        // Update angle based on time for fixed rpm
        GLdouble curTime = glfwGetTime();
        if (animate) {
            update_scene_graph(curTime - elTime);
        }
        elTime = curTime;
        // Swap buffer onto screen
        glfwSwapBuffers( window );
    }

    // Close window
    glfwTerminate();
    return 0;
}

void display( )
{
	// Clear window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	draw_background();

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
    proj_matrix = ortho(-15.0f*xratio, 15.0f*xratio, -15.0f*yratio, 15.0f*yratio, -50.0f, 50.0f);

    // Set camera matrix
    camera_matrix = lookat(eye, center, up);

    // Render objects
	render_scene();

	glFlush();
}

void render_scene( ) {
    traverse_scene_graph(&base, mat4().identity());
}

void traverse_scene_graph(BaseNode *node, mat4 baseTransform) {
	mat4 model_matrix;

    // Stop when at bottom of branch
    if (node == NULL) {
        return;
    }

    // Apply local transformation and render
    model_matrix = baseTransform*node->ModelTransform;

    node->draw(proj_matrix, camera_matrix, model_matrix);

    // Recurse vertically if possible (depth-first)
    if (node->child != NULL) {
        traverse_scene_graph(node->child, model_matrix);
    }

    // Remove local transformation and recurse horizontal
    if (node->sibling != NULL) {
        traverse_scene_graph(node->sibling, baseTransform);
    }
}


void build_geometry( )
{
    // Generate vertex arrays for objects
    glGenVertexArrays(NumVAOs, VAOs);

    load_object(Cube);

    load_object(Sphere);

    // Define 3D vertices for cube
    vector<vec4> vertices = {
            vec4(1.0f,  -1.0f, 1.0f, 1.0f),    // front
            vec4(1.0f,  1.0f,  1.0f, 1.0f),
            vec4(-1.0f, 1.0f,  1.0f, 1.0f),
            vec4(-1.0f, 1.0f,  1.0f, 1.0f),
            vec4(-1.0f, -1.0f, 1.0f, 1.0f),
            vec4(1.0f,  -1.0f, 1.0f, 1.0f),

            vec4(-1.0f, -1.0f, -1.0f, 1.0f),   // back
            vec4(-1.0f, 1.0f,  -1.0f, 1.0f),
            vec4(1.0f,  1.0f,  -1.0f, 1.0f),
            vec4(1.0f,  1.0f,  -1.0f, 1.0f),
            vec4(1.0f,  -1.0f, -1.0f, 1.0f),
            vec4(-1.0f, -1.0f, -1.0f, 1.0f),

            vec4(-1.0f, -1.0f, -1.0f, 1.0f),   // left
            vec4(-1.0f, -1.0f, 1.0f, 1.0f),
            vec4(-1.0f, 1.0f,  1.0f, 1.0f),
            vec4(-1.0f, 1.0f,  1.0f, 1.0f),
            vec4(-1.0f, 1.0f,  -1.0f, 1.0f),
            vec4(-1.0f, -1.0f, -1.0f, 1.0f),

            vec4(1.0f,  -1.0f, -1.0f, 1.0f),   // right
            vec4(1.0f,  1.0f,  -1.0f, 1.0f),
            vec4(1.0f,  1.0f,  1.0f, 1.0f),
            vec4(1.0f,  1.0f,  1.0f, 1.0f),
            vec4(1.0f,  -1.0f, 1.0f, 1.0f),
            vec4(1.0f,  -1.0f, -1.0f, 1.0f),

            vec4(-1.0f, 1.0f,  -1.0f, 1.0f),   // top
            vec4(-1.0f, 1.0f,  1.0f, 1.0f),
            vec4(1.0f,  1.0f,  1.0f, 1.0f),
            vec4(1.0f,  1.0f,  1.0f, 1.0f),
            vec4(1.0f,  1.0f,  -1.0f, 1.0f),
            vec4(-1.0f, 1.0f,  -1.0f, 1.0f),

            vec4(-1.0f, -1.0f, -1.0f, 1.0f),   // bottom
            vec4(1.0f,  -1.0f, -1.0f, 1.0f),
            vec4(1.0f,  -1.0f, 1.0f, 1.0f),
            vec4(1.0f,  -1.0f, 1.0f, 1.0f),
            vec4(-1.0f, -1.0f, 1.0f, 1.0f),
            vec4(-1.0f, -1.0f, -1.0f, 1.0f)
    };

    vector<vec3> normals = {
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f),
            vec3(1.0f,  0.0f, 0.0f)
    };

    // TODO: Define texture coordinates for torso
    vector<vec2> uvCoords = {
            vec2(180.0f/512.0f, -256.0f/256.0f),
            vec2(180.0f/512.0f, 0.0f),
            vec2(0.0f, 0.0f),
            vec2(0.0f, 0.0f),
            vec2(0.0f, -256.0f/256.0f),     // FRONT
            vec2(180.0f/512.0f, -256.0f/256.0f),

            vec2(180.0f/512.0f, -256.0f/256.0f),
            vec2(180.0f/512.0f, 0.0f),
            vec2(360.0f/512.0f, 0.0f),
            vec2(360.0f/512.0f, 0.0f),
            vec2(360.0f/512.0f, -256.0f/256.0f),
            vec2(180.0f/512.0f, -256.0f/256.0f),     // BACK

            vec2(360.0f/512.0f, -227.0f/256.0f),
            vec2(436.0f/512.0f, -227.0f/256.0f),
            vec2(436.0f/512.0f, 0.0f),
            vec2(436.0f/512.0f, 0.0f),
            vec2(360.0f/512.0f, 0.0f),
            vec2(360.0f/512.0f, -227.0f/256.0f),     // RIGHT

            vec2(512.0f/512.0f, -227.0f/256.0f),
            vec2(512.0f/512.0f, 0.0f),
            vec2(436.0f/512.0f, 0.0f),
            vec2(436.0f/512.0f, 0.0f),
            vec2(436.0f/512.0f, -227.0f/256.0f),     // LEFT
            vec2(512.0f/512.0f, -227.0f/256.0f),

    };

    numVertices[TexCube] = vertices.size();
    // Create and load object buffers
    glGenBuffers(NumObjBuffers, ObjBuffers[TexCube]);
    glBindVertexArray(VAOs[TexCube]);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[TexCube][PosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*posCoords*numVertices[TexCube], vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[TexCube][NormBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*normCoords*numVertices[TexCube], normals.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[TexCube][TexBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*texCoords*numVertices[TexCube], uvCoords.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    vertices.clear();
    normals.clear();
    uvCoords.clear();

    vertices.push_back(vec4(3.0f, 3.0f, 0.0f, 1.0f));
    vertices.push_back(vec4(-3.0f, 3.0f, 0.0f, 1.0f));
    vertices.push_back(vec4(-3.0f, -3.0f, 0.0f, 1.0f));
    vertices.push_back(vec4(-3.0f, -3.0f, 0.0f, 1.0f));
    vertices.push_back(vec4(3.0f, -3.0f, 0.0f, 1.0f));
    vertices.push_back(vec4(3.0f, 3.0f, 0.0f, 1.0f));

    // TODO: Define texture coordinates for background
    uvCoords.push_back(vec2(2.0f, 2.0f));
    uvCoords.push_back(vec2(-1.0f, 2.0f));
    uvCoords.push_back(vec2(-1.0f, -1.0f));
    uvCoords.push_back(vec2(-1.0f, -1.0f));
    uvCoords.push_back(vec2(2.0f, -1.0f));
    uvCoords.push_back(vec2(2.0f, 2.0f));

    normals.push_back(vec3(1.0f, 0.0f, 0.0f));
    normals.push_back(vec3(1.0f, 0.0f, 0.0f));
    normals.push_back(vec3(1.0f, 0.0f, 0.0f));
    normals.push_back(vec3(1.0f, 0.0f, 0.0f));
    normals.push_back(vec3(1.0f, 0.0f, 0.0f));
    normals.push_back(vec3(1.0f, 0.0f, 0.0f));

    numVertices[Background] = vertices.size();

    glBindVertexArray(VAOs[Background]);
    glGenBuffers(NumObjBuffers, ObjBuffers[Background]);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[Background][PosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*posCoords*numVertices[Background], vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[Background][NormBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*normCoords*numVertices[Background], normals.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[Background][TexBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*texCoords*numVertices[Background], uvCoords.data(), GL_STATIC_DRAW);
}

void build_lights( ) {
    // White directional light
    LightProperties whiteDirLight = {DIRECTIONAL, //type
                                  {0.0f, 0.0f, 0.0f}, //pad
                                  vec4(0.0f, 0.0f, 0.0f, 1.0f), //ambient
                                  vec4(1.0f, 1.0f, 1.0f, 1.0f), //diffuse
                                  vec4(1.0f, 1.0f, 1.0f, 1.0f), //specular
                                  vec4(0.0f, 0.0f, 0.0f, 1.0f),  //position
                                  vec4(-1.0f, -1.0f, -1.0f, 0.0f), //direction
                                  0.0f,   //cutoff
                                  0.0f,  //exponent
                                  {0.0f, 0.0f}  //pad2
    };

    // Green point light
    LightProperties yellowPointLight = {POINT, //type
                                  {0.0f, 0.0f, 0.0f}, //pad
                                  vec4(0.0f, 0.0f, 0.0f, 1.0f), //ambient
                                  vec4(0.5f, 0.5f, 0.0f, 1.0f), //diffuse
                                  vec4(0.7f, 0.7f, 0.0f, 1.0f), //specular
                                  vec4(10.0f, 10.0f, 10.0f, 1.0f),  //position
                                  vec4(0.0f, 0.0f, 0.0f, 0.0f), //direction
                                  0.0f,   //cutoff
                                  0.0f,  //exponent
                                  {0.0f, 0.0f}  //pad2
    };

    //Red spot light
    LightProperties redSpotLight = {SPOT, //type
                                  {0.0f, 0.0f, 0.0f}, //pad
                                  vec4(0.0f, 0.0f, 0.0f, 1.0f), //ambient
                                  vec4(0.0f, 1.0f, 0.0f, 1.0f), //diffuse
                                  vec4(1.0f, 1.0f, 1.0f, 1.0f), //specular
                                  vec4(0.0f, 6.0f, 4.0f, 1.0f),  //position
                                  vec4(0.0f, -1.0f, 0.0f, 0.0f), //direction
                                  30.0f,   //cutoff
                                  30.0f,  //exponent
                                  {0.0f, 0.0f}  //pad2
    };


	Lights.push_back(whiteDirLight);
	Lights.push_back(yellowPointLight);
	Lights.push_back(redSpotLight);

	numLights = Lights.size();

    glGenBuffers(NumLightBuffers, LightBuffers);
    glBindBuffer(GL_UNIFORM_BUFFER, LightBuffers[LightBuffer]);
    glBufferData(GL_UNIFORM_BUFFER, Lights.size()*sizeof(LightProperties), Lights.data(), GL_STATIC_DRAW);
}

void build_materials( ) {
	// TODO: Make materials
    // Create skin material
    MaterialProperties skin = {vec4(0.33f, 0.22f, 0.03f, 1.0f), //ambient
                                vec4(0.78f, 0.57f, 0.11f, 1.0f), //diffuse
                                vec4(0.99f, 0.91f, 0.81f, 1.0f), //specular
                                10.0f, //shininess
                                {0.0f, 0.0f, 0.0f}  //pad
    };


    // TODO: Make additional materials
    MaterialProperties redGlass = {vec4(0.0f, 0.0f, 0.0f, 0.0f), //ambient
                               vec4(0.78f, 0.00f, 0.00f, 0.35f), //diffuse
                               vec4(0.99f, 0.91f, 0.81f, 1.0f), //specular
                               15.0f, //shininess
                               {0.0f, 0.0f, 0.0f}  //pad
    };


    // Add materials to Materials vector
    Materials.push_back(skin);
    Materials.push_back(redGlass);


    glGenBuffers(NumMaterialBuffers, MaterialBuffers);
    glBindBuffer(GL_UNIFORM_BUFFER, MaterialBuffers[MaterialBuffer]);
    glBufferData(GL_UNIFORM_BUFFER, Materials.size()*sizeof(MaterialProperties), Materials.data(), GL_STATIC_DRAW);
}

void build_textures( ) {
    int w, h, n;
    int force_channels = 4;
    unsigned char *image_data;

    // Create textures and activate unit 0
    glGenTextures( NumTextures,  TextureIDs);
    glActiveTexture( GL_TEXTURE0 );

    for (int i = 0; i < NumTextures; i++) {
        // Load image from file
        image_data = stbi_load(texFiles[i], &w, &h, &n, force_channels);
        if (!image_data) {
            fprintf(stderr, "ERROR: could not load %s\n", texFiles[i]);
        }
        // NPOT check for power of 2 dimensions
        if ((w & (w - 1)) != 0 || (h & (h - 1)) != 0) {
            fprintf(stderr, "WARNING: texture %s is not power-of-2 dimensions\n",
                    texFiles[i]);
        }
        int width_in_bytes = w * 4;
        unsigned char *top = NULL;
        unsigned char *bottom = NULL;
        unsigned char temp = 0;
        int half_height = h / 2;

        for ( int row = 0; row < half_height; row++ ) {
            top = image_data + row * width_in_bytes;
            bottom = image_data + ( h - row - 1 ) * width_in_bytes;
            for ( int col = 0; col < width_in_bytes; col++ ) {
                temp = *top;
                *top = *bottom;
                *bottom = temp;
                top++;
                bottom++;
            }
        }

        // TODO: Bind current texture id
        glBindTexture(GL_TEXTURE_2D, TextureIDs[i]);
        // TODO: Load image data into texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     image_data);
        glGenerateMipmap(GL_TEXTURE_2D);
        // TODO: Set scaling modes
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // TODO: Set wrapping modes
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Set maximum anisotropic filtering for system
        GLfloat max_aniso = 0.0f;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso);
        // set the maximum!
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso);
    }
}


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Move hexagon with arrow keys
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }

    // Adjust azimuth
    if (key == GLFW_KEY_A) {
        azimuth += daz;
        if (azimuth > 360.0) {
            azimuth -= 360.0;
        }
    } else if (key == GLFW_KEY_D) {
        azimuth -= daz;
        if (azimuth < 0.0)
        {
            azimuth += 360.0;
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

    // Compute updated camera position
    GLfloat x, y, z;
    x = (GLfloat)(radius*sin(azimuth*DEG2RAD)*sin(elevation*DEG2RAD));
    y = (GLfloat)(radius*cos(elevation*DEG2RAD));
    z = (GLfloat)(radius*cos(azimuth*DEG2RAD)*sin(elevation*DEG2RAD));
    eye = vec3(x,y,z);

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
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[obj][TexBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*texCoords*numVertices[obj], uvCoords.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void draw_background(){
	// TODO: Draw background using Background object
    // Set anisotropic scaling
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
    // TODO: Set default orthographic projection
    proj_matrix = ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

    // TODO: Set default camera matrix
    camera_matrix = mat4().identity();

    // Select shader program
    glUseProgram(tex_program);
    // Pass projection matrix to shader
    glUniformMatrix4fv(tex_proj_mat_loc, 1, GL_FALSE, proj_matrix);
    // Pass camera matrix to shader
    glUniformMatrix4fv(tex_camera_mat_loc, 1, GL_FALSE, camera_matrix);
    // TODO: Set default model matrix
    model_matrix = mat4().identity();
    glUniformMatrix4fv(tex_model_mat_loc, 1, GL_FALSE, model_matrix);
    glBindVertexArray(VAOs[Background]);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[Background][PosBuffer]);
    glVertexAttribPointer(tex_vPos, posCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(tex_vPos);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[Background][TexBuffer]);
    glVertexAttribPointer(tex_vTex, texCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(tex_vTex);
    // TODO: Bind background texture id
    glBindTexture(GL_TEXTURE_2D, TextureIDs[YCP]);
    // TODO: Draw background with depth buffer writes disabled
    glDepthMask(GL_FALSE);
    glDrawArrays(GL_TRIANGLES, 0, numVertices[YCP]);
    glDepthMask(GL_TRUE);
}

void build_scene_graph( ) {
    // TODO: MILESTONE 1
    // TODO: Add scene graph nodes
    // TODO: Add base node
    base.set_shader(tex_program, tex_proj_mat_loc, tex_camera_mat_loc, tex_model_mat_loc);
    base.set_buffers(VAOs[Sphere], ObjBuffers[Sphere][PosBuffer], tex_vPos, posCoords, ObjBuffers[Sphere][TexBuffer], tex_vTex, texCoords, numVertices[Sphere]);
    base.TexID = TextureIDs[Face];
    base.set_base_transform(translate(0.0f, HEAD_HEIGHT+TORSO_HEIGHT, 0.0f)*rotate(180.0f, 1.0f, 0.0f, 0.0f)*scale(vec3(HEAD_WIDTH, HEAD_HEIGHT, HEAD_DEPTH)));
    base.sibling = nullptr;
    base.child = &torso;

    // TODO: Add torso node
    torso.set_shader(tex_program, tex_proj_mat_loc, tex_camera_mat_loc, tex_model_mat_loc);
    torso.set_buffers(VAOs[TexCube], ObjBuffers[TexCube][PosBuffer], tex_vPos, posCoords, ObjBuffers[TexCube][TexBuffer], tex_vTex, texCoords, numVertices[TexCube]);
    torso.TexID = TextureIDs[Shirt];
    torso.set_base_transform(translate(vec3(1.0f, 0.0f, 1.0f))*scale(vec3(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH)));
    torso.sibling = &left_upper_arm;
    torso.child = &left_upper_leg;

    // TODO: Add left upper arm node
    left_upper_arm.set_shader(light_program, light_proj_mat_loc, light_camera_mat_loc, light_model_mat_loc);
    left_upper_arm.NormMatPtr = light_norm_mat_loc;
    left_upper_arm.set_buffers(VAOs[Cube], ObjBuffers[Cube][PosBuffer], light_vPos, posCoords, ObjBuffers[Cube][NormBuffer], light_vNorm, normCoords, numVertices[Cube]);
    left_upper_arm.set_materials(MaterialBuffers[MaterialBuffer], materials_block_idx, Materials.size()*sizeof(MaterialProperties), material_loc, Skin, false);
    left_upper_arm.set_lights(LightBuffers[LightBuffer], lights_block_idx, Lights.size()*sizeof(LightProperties), num_lights_loc, Lights.size());
    left_upper_arm.set_eye(light_eye_loc, eye);
    left_upper_arm.set_base_transform(translate((TORSO_WIDTH+UPPER_ARM_WIDTH)*1.2f, UPPER_ARM_HEIGHT, 0.0f)*scale(vec3(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_DEPTH)));
    left_upper_arm.sibling = &right_upper_arm;
    left_upper_arm.child = &left_lower_arm;

    // TODO: Add right upper arm node
    right_upper_arm.set_shader(light_program, light_proj_mat_loc, light_camera_mat_loc, light_model_mat_loc);
    right_upper_arm.NormMatPtr = light_norm_mat_loc;
    right_upper_arm.set_buffers(VAOs[Cube], ObjBuffers[Cube][PosBuffer], light_vPos, posCoords, ObjBuffers[Cube][NormBuffer], light_vNorm, normCoords, numVertices[Cube]);
    right_upper_arm.set_materials(MaterialBuffers[MaterialBuffer], materials_block_idx, Materials.size()*sizeof(MaterialProperties), material_loc, Skin, false);
    right_upper_arm.set_lights(LightBuffers[LightBuffer], lights_block_idx, Lights.size()*sizeof(LightProperties), num_lights_loc, Lights.size());
    right_upper_arm.set_eye(light_eye_loc, eye);
    right_upper_arm.set_base_transform(translate((-TORSO_WIDTH-UPPER_ARM_WIDTH)*1.2f, UPPER_ARM_HEIGHT, 0.0f)*scale(vec3(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_DEPTH)));
    right_upper_arm.sibling = nullptr;
    right_upper_arm.child = &right_lower_arm;

    // TODO: MILESTONE 1 END

//    // TODO: Add left lower arm node
//    left_lower_arm.set_shader(light_program, light_proj_mat_loc, light_camera_mat_loc, light_model_mat_loc);
//    left_lower_arm. = light_norm_mat_loc;
//    left_lower_arm.set_buffers(VAOs[TexCube], ObjBuffers[TexCube][PosBuffer], light_vPos, posCoords, ObjBuffers[TexCube][NormBuffer], light_vNorm, normCoords, numVertices[Cylinder]);
//    left_lower_arm.(MaterialBuffers[MaterialBuffer], materials_block_idx, Materials.size()*sizeof(MaterialProperties), material_loc, Materials[Skin]);
//    left_lower_arm.set_lights(LightBuffers[LightBuffer], lights_block_idx, Lights.size()*sizeof(LightProperties), num_lights_loc, Lights.size());
//    left_lower_arm.set_eye(light_eye_loc, eye);
//    left_lower_arm.set_base_transform(scale(vec3(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_DEPTH)));
//    left_lower_arm.update_transform(rotate(theta, vec3(0.0f, 1.0f, 0.0f)));
//    left_lower_arm.sibling = nullptr;
//    left_lower_arm.child = &&bball;

//    // TODO: Add right lower arm node
//    right_lower_arm.set_shader(light_program, light_proj_mat_loc, light_camera_mat_loc, light_model_mat_loc);
//    right_lower_arm. = light_norm_mat_loc;
//    right_lower_arm.set_buffers(VAOs[TexCube], ObjBuffers[TexCube][PosBuffer], light_vPos, posCoords, ObjBuffers[TexCube][NormBuffer], light_vNorm, normCoords, numVertices[Cylinder]);
//    right_lower_arm.(MaterialBuffers[MaterialBuffer], materials_block_idx, Materials.size()*sizeof(MaterialProperties), material_loc, Materials[Skin]);
//    right_lower_arm.set_lights(LightBuffers[LightBuffer], lights_block_idx, Lights.size()*sizeof(LightProperties), num_lights_loc, Lights.size());
//    right_lower_arm.set_eye(light_eye_loc, eye);
//    right_lower_arm.set_base_transform(scale(vec3(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_DEPTH)));
//    right_lower_arm.update_transform(rotate(theta, vec3(0.0f, 1.0f, 0.0f)));
//    right_lower_arm.sibling = nullptr;
//    right_lower_arm.child = &right_lower_arm;

//    // TODO: Add left upper leg node
//    left_upper_leg.set_shader(light_program, light_proj_mat_loc, light_camera_mat_loc, light_model_mat_loc);
//    left_upper_leg. = light_norm_mat_loc;
//    left_upper_leg.set_buffers(VAOs[TexCube], ObjBuffers[TexCube][PosBuffer], light_vPos, posCoords, ObjBuffers[TexCube][NormBuffer], light_vNorm, normCoords, numVertices[Cylinder]);
//    left_upper_leg.(MaterialBuffers[MaterialBuffer], materials_block_idx, Materials.size()*sizeof(MaterialProperties), material_loc, Materials[Skin]);
//    left_upper_leg.set_lights(LightBuffers[LightBuffer], lights_block_idx, Lights.size()*sizeof(LightProperties), num_lights_loc, Lights.size());
//    left_upper_leg.set_eye(light_eye_loc, eye);
//    left_upper_leg.set_base_transform(scale(vec3(UPPER_LEG_WIDTH, UPPER_LEG_HEIGHT, UPPER_LEG_DEPTH)));
//    left_upper_leg.update_transform(rotate(theta, vec3(0.0f, 1.0f, 0.0f)));
//    left_upper_leg.sibling = &left_upper_leg;
//    left_upper_leg.child = &left_lower_leg;

//    // TODO: Add right upper leg node
//    right_upper_leg.set_shader(light_program, light_proj_mat_loc, light_camera_mat_loc, light_model_mat_loc);
//    right_upper_leg. = light_norm_mat_loc;
//    right_upper_leg.set_buffers(VAOs[TexCube], ObjBuffers[TexCube][PosBuffer], light_vPos, posCoords, ObjBuffers[TexCube][NormBuffer], light_vNorm, normCoords, numVertices[Cylinder]);
//    right_upper_leg.(MaterialBuffers[MaterialBuffer], materials_block_idx, Materials.size()*sizeof(MaterialProperties), material_loc, Materials[Skin]);
//    right_upper_leg.set_lights(LightBuffers[LightBuffer], lights_block_idx, Lights.size()*sizeof(LightProperties), num_lights_loc, Lights.size());
//    right_upper_leg.set_eye(light_eye_loc, eye);
//    right_upper_leg.set_base_transform(scale(vec3(UPPER_LEG_WIDTH, UPPER_LEG_HEIGHT, UPPER_LEG_DEPTH)));
//    right_upper_leg.update_transform(rotate(theta, vec3(0.0f, 1.0f, 0.0f)));
//    right_upper_leg.sibling = nullptr;
//    right_upper_leg.child = &right_lower_leg;

//    // TODO: Add left lower leg node
//    left_lower_leg.set_shader(light_program, light_proj_mat_loc, light_camera_mat_loc, light_model_mat_loc);
//    left_lower_leg. = light_norm_mat_loc;
//    left_lower_leg.set_buffers(VAOs[TexCube], ObjBuffers[TexCube][PosBuffer], light_vPos, posCoords, ObjBuffers[TexCube][NormBuffer], light_vNorm, normCoords, numVertices[Cylinder]);
//    left_lower_leg.(MaterialBuffers[MaterialBuffer], materials_block_idx, Materials.size()*sizeof(MaterialProperties), material_loc, Materials[Skin]);
//    left_lower_leg.set_lights(LightBuffers[LightBuffer], lights_block_idx, Lights.size()*sizeof(LightProperties), num_lights_loc, Lights.size());
//    left_lower_leg.set_eye(light_eye_loc, eye);
//    left_lower_leg.set_base_transform(scale(vec3(LOWER_LEG_WIDTH, LOWER_LEG_HEIGHT, LOWER_LEG_DEPTH)));
//    left_lower_leg.update_transform(rotate(theta, vec3(0.0f, 1.0f, 0.0f)));
//    left_lower_leg.sibling = nullptr;
//    left_lower_leg.child = &bball;

//    // TODO: Add right lower leg node
//    right_lower_leg.set_shader(light_program, light_proj_mat_loc, light_camera_mat_loc, light_model_mat_loc);
//    right_lower_leg. = light_norm_mat_loc;
//    right_lower_leg.set_buffers(VAOs[TexCube], ObjBuffers[TexCube][PosBuffer], light_vPos, posCoords, ObjBuffers[TexCube][NormBuffer], light_vNorm, normCoords, numVertices[Cylinder]);
//    right_lower_leg.(MaterialBuffers[MaterialBuffer], materials_block_idx, Materials.size()*sizeof(MaterialProperties), material_loc, Materials[Skin]);
//    right_lower_leg.set_lights(LightBuffers[LightBuffer], lights_block_idx, Lights.size()*sizeof(LightProperties), num_lights_loc, Lights.size());
//    right_lower_leg.set_eye(light_eye_loc, eye);
//    right_lower_leg.set_base_transform(scale(vec3(LOWER_LEG_WIDTH, LOWER_LEG_HEIGHT, LOWER_LEG_DEPTH)));
//    right_lower_leg.update_transform(rotate(theta, vec3(0.0f, 1.0f, 0.0f)));
//    right_lower_leg.sibling = nullptr;
//    right_lower_leg.child = &right_lower_leg;

//    // TODO: Add basketball node
//    bball.set_shader(light_program, light_proj_mat_loc, light_camera_mat_loc, light_model_mat_loc);
//    bball. = light_norm_mat_loc;
//    bball.set_buffers(VAOs[TexCube], ObjBuffers[TexCube][PosBuffer], light_vPos, posCoords, ObjBuffers[TexCube][NormBuffer], light_vNorm, normCoords, numVertices[Cylinder]);
//    bball.(MaterialBuffers[MaterialBuffer], materials_block_idx, Materials.size()*sizeof(MaterialProperties), material_loc, Materials[Skin]);
//    bball.set_lights(LightBuffers[LightBuffer], lights_block_idx, Lights.size()*sizeof(LightProperties), num_lights_loc, Lights.size());
//    bball.set_eye(light_eye_loc, eye);
//    bball.set_base_transform(scale(vec3(1.0f, 1.0f, 1.0f)));
//    bball.update_transform(rotate(theta, vec3(0.0f, 1.0f, 0.0f)));
//    bball.sibling = nullptr;
//    bball.child = nullptr;

}

void update_scene_graph(GLdouble dT) {
	// TODO: Update scene graph update transformations
	
}
