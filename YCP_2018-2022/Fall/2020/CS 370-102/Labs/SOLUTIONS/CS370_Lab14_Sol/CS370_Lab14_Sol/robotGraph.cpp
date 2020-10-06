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

using namespace vmath;
using namespace std;

enum VAO_IDs {Cube, Cylinder, Sphere, NumVAOs};
enum ObjBuffer_IDs {PosBuffer, NormBuffer, TexBuffer, NumObjBuffers};
enum LightBuffer_IDs {LightBuffer, NumLightBuffers};
enum MaterialBuffer_IDs {MaterialBuffer, NumMaterialBuffers};
enum MaterialNames {Brass, RedPlastic};
enum Textures {Earth, NumTextures};

GLuint VAOs[NumVAOs];
GLuint ObjBuffers[NumVAOs][NumObjBuffers];
GLuint LightBuffers[NumLightBuffers];
GLuint MaterialBuffers[NumMaterialBuffers];
GLuint TextureIDs[NumTextures];

GLint numVertices[NumVAOs];
GLint posCoords = 4;
GLint normCoords = 3;
GLint texCoords = 2;

vector<const char *> objFiles = {"../models/cube.obj", "../models/cylinder.obj", "../models/uv_sphere.obj"};
vector<const char *> texFiles = {"../textures/earth.bmp"};
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
mat4 camera_matrix;
vector<LightProperties> Lights;
vector<MaterialProperties> Materials;
GLuint MaterialIdx[NumVAOs] = {Brass, RedPlastic};
GLuint numLights;

// Scene graph nodes
MatNode base;
MatNode lower_arm;
MatNode left_upper_arm;
MatNode right_upper_arm;
TexNode earth;

// Define object dimensions
#define BASE_RADIUS 2.0f
#define BASE_HEIGHT 1.0f
#define LOWER_HEIGHT 2.0f
#define LOWER_WIDTH 1.0f
#define LOWER_DEPTH 0.5f
#define UPPER_HEIGHT 1.5f
#define UPPER_WIDTH 0.5f
#define UPPER_DEPTH 0.5f
// Rotation angles
GLfloat theta = 0.0f;
GLfloat dtheta = 1.0f;
GLfloat phi = 0.0f;
GLfloat dphi = 1.0f;
GLfloat left_psi = 0.0f;
GLfloat right_psi = 0.0f;
GLfloat dpsi = 1.0f;
GLfloat earth_angle = 0.0f;
GLfloat rpm = 10.0f;
GLdouble elTime = 0.0;


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

int main(int argc, char**argv)
{
	// Create OpenGL window
	GLFWwindow* window = CreateWindow("Robot Graph");
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

	// Start loop
    while ( !glfwWindowShouldClose( window ) ) {
    	// Draw graphics
        display();
        // Update other events like input handling
        glfwPollEvents();
        // Update angle based on time for fixed rpm
        GLdouble curTime = glfwGetTime();
        earth_angle += (curTime-elTime)*(rpm/60.0)*360.0;
        elTime = curTime;
        // TODO: Update earth node transformation
        earth.update_transform(translate(vec3(0.0f, 3.0f, 5.0f))*rotate(earth_angle, vec3(0.0f, 1.0f, 0.0f)));
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
    proj_matrix = ortho(-10.0f*xratio, 10.0f*xratio, -10.0f*yratio, 10.0f*yratio, -10.0f, 10.0f);

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

void build_scene_graph( ) {
	// TODO: Add base node
    base.set_shader(light_program, light_proj_mat_loc, light_camera_mat_loc, light_model_mat_loc);
    base.NormMatPtr = light_norm_mat_loc;
    base.set_buffers(VAOs[Cylinder], ObjBuffers[Cylinder][PosBuffer], light_vPos, posCoords, ObjBuffers[Cylinder][NormBuffer], light_vNorm, normCoords, numVertices[Cylinder]);
	base.set_materials(MaterialBuffers[MaterialBuffer], materials_block_idx, Materials.size()*sizeof(MaterialProperties), material_loc, MaterialIdx[Cylinder]);
    base.set_lights(LightBuffers[LightBuffer], lights_block_idx, Lights.size()*sizeof(LightProperties), num_lights_loc, Lights.size());
    base.set_eye(light_eye_loc, eye);
    base.set_base_transform(scale(vec3(BASE_RADIUS, BASE_HEIGHT, BASE_RADIUS)));
	base.update_transform(rotate(theta, vec3(0.0f, 1.0f, 0.0f)));
    base.sibling = &earth;
    base.child = &lower_arm;

	// TODO: Add lower arm node (child of base)
    lower_arm.set_shader(light_program, light_proj_mat_loc, light_camera_mat_loc, light_model_mat_loc);
    lower_arm.NormMatPtr = light_norm_mat_loc;
    lower_arm.set_buffers(VAOs[Cube], ObjBuffers[Cube][PosBuffer], light_vPos, posCoords, ObjBuffers[Cube][NormBuffer], light_vNorm, normCoords, numVertices[Cube]);
    lower_arm.set_materials(MaterialBuffers[MaterialBuffer], materials_block_idx, Materials.size()*sizeof(MaterialProperties), material_loc, MaterialIdx[Cube]);
    lower_arm.set_lights(LightBuffers[LightBuffer], lights_block_idx, Lights.size()*sizeof(LightProperties), num_lights_loc, Lights.size());
    lower_arm.set_eye(light_eye_loc, eye);
    lower_arm.set_base_transform(translate(vec3(0.0f, LOWER_HEIGHT, 0.0f))*scale(vec3(LOWER_WIDTH, LOWER_HEIGHT, LOWER_DEPTH)));
    lower_arm.update_transform(translate(vec3(0.0f, BASE_HEIGHT, 0.0f))*rotate(phi, vec3(1.0f, 0.0f, 0.0f)));
    lower_arm.sibling = NULL;
    lower_arm.child = &left_upper_arm;

	// TODO: Add left upper arm node (child of lower arm)
    left_upper_arm.set_shader(light_program, light_proj_mat_loc, light_camera_mat_loc, light_model_mat_loc);
    left_upper_arm.NormMatPtr = light_norm_mat_loc;
    left_upper_arm.set_buffers(VAOs[Cube], ObjBuffers[Cube][PosBuffer], light_vPos, posCoords, ObjBuffers[Cube][NormBuffer], light_vNorm, normCoords, numVertices[Cube]);
    left_upper_arm.set_materials(MaterialBuffers[MaterialBuffer], materials_block_idx, Materials.size()*sizeof(MaterialProperties), material_loc, MaterialIdx[Cylinder]);
    left_upper_arm.set_lights(LightBuffers[LightBuffer], lights_block_idx, Lights.size()*sizeof(LightProperties), num_lights_loc, Lights.size());
    left_upper_arm.set_eye(light_eye_loc, eye);
    left_upper_arm.set_base_transform(translate(vec3(0.0f, UPPER_HEIGHT, 0.0f))*scale(vec3(UPPER_WIDTH, UPPER_HEIGHT, UPPER_DEPTH)));
    left_upper_arm.update_transform(translate(vec3((LOWER_WIDTH+UPPER_WIDTH), 2*LOWER_HEIGHT, 0.0f))*rotate(left_psi, vec3(1.0f, 0.0f, 0.0f)));
    left_upper_arm.sibling = &right_upper_arm;
    left_upper_arm.child = NULL;

	// TODO: Add right upper arm node (sibling of left upper arm)
    right_upper_arm.set_shader(light_program, light_proj_mat_loc, light_camera_mat_loc, light_model_mat_loc);
    right_upper_arm.NormMatPtr = light_norm_mat_loc;
    right_upper_arm.set_buffers(VAOs[Cube], ObjBuffers[Cube][PosBuffer], light_vPos, posCoords, ObjBuffers[Cube][NormBuffer], light_vNorm, normCoords, numVertices[Cube]);
    right_upper_arm.set_materials(MaterialBuffers[MaterialBuffer], materials_block_idx, Materials.size()*sizeof(MaterialProperties), material_loc, MaterialIdx[Cylinder]);
    right_upper_arm.set_lights(LightBuffers[LightBuffer], lights_block_idx, Lights.size()*sizeof(LightProperties), num_lights_loc, Lights.size());
    right_upper_arm.set_eye(light_eye_loc, eye);
    right_upper_arm.set_base_transform(translate(vec3(0.0f, UPPER_HEIGHT, 0.0f))*scale(vec3(UPPER_WIDTH, UPPER_HEIGHT, UPPER_DEPTH)));
    right_upper_arm.update_transform(translate(vec3((-LOWER_WIDTH-UPPER_WIDTH), 2*LOWER_HEIGHT, 0.0f))*rotate(right_psi, vec3(1.0f, 0.0f, 0.0f)));
    right_upper_arm.sibling = NULL;
    right_upper_arm.child = NULL;

	// TODO: Add earth node (sibling of base)
    earth.set_shader(tex_program, tex_proj_mat_loc, tex_camera_mat_loc, tex_model_mat_loc);
    earth.set_buffers(VAOs[Sphere], ObjBuffers[Sphere][PosBuffer], tex_vPos, posCoords, ObjBuffers[Sphere][TexBuffer], tex_vTex, texCoords, numVertices[Sphere]);
    earth.TexID = TextureIDs[Earth];
    earth.set_base_transform(scale(1.5f, 1.5f, 1.5f));
    earth.update_transform(translate(vec3(0.0f, 3.0f, 5.0f))*rotate(earth_angle,vec3(0.0f, 1.0f, 0.0f)));
    earth.sibling = NULL;
    earth.child = NULL;

}

void build_geometry( )
{
    // Generate vertex arrays for objects
    glGenVertexArrays(NumVAOs, VAOs);

    load_object(Cube);

    load_object(Cylinder);

    load_object(Sphere);
}

void build_lights( ) {
    // Directional white light
    Lights.push_back(
            {DIRECTIONAL, {0.0f, 0.0f, 0.0f}, //type + pad
             {0.0f, 0.0f, 0.0f, 0.0f}, //ambient
             {1.0f, 1.0f, 1.0f, 1.0f}, //diffuse
             {1.0f, 1.0f, 1.0f, 1.0f}, //specular
             {0.0f, 0.0f, 0.0f, 1.0f},  //position
             {-1.0f, -1.0f, -1.0f}, //direction
             0.0f,       //pad2
             0.0f,   //cutoff
             0.0f,  //exponent
             {0.0f, 0.0f}  //pad3
            });
    // Point green light
    Lights.push_back(
            {OFF, {0.0f, 0.0f, 0.0f}, //type + pad
             {0.0f, 0.0f, 0.0f, 0.0f}, //ambient
             {0.0f, 1.0f, 0.0f, 1.0f}, //diffuse
             {0.0f, 1.0f, 0.0f, 1.0f}, //specular
             {3.0f, 3.0f, 3.0f, 1.0f},  //position
             {0.0f, 0.0f, 0.0f}, //direction
             0.0f,       //pad2
             0.0f,   //cutoff
             0.0f,  //exponent
             {0.0f, 0.0f}  //pad3
            });
    // Spot red light
    Lights.push_back(
            {SPOT, {0.0f, 0.0f, 0.0f}, //type + pad
             {0.0f, 0.0f, 0.0f, 0.0f}, //ambient
             {1.0f, 0.0f, 0.0f, 1.0f}, //diffuse
             {1.0f, 1.0f, 1.0f, 1.0f}, //specular
             {0.0f, 6.0f, 0.0f, 1.0f},  //position
             {0.0f, -1.0f, 0.0f}, //direction
             0.0f,       //pad2
             30.0f,   //cutoff
             0.0f,  //exponent
             {0.0f, 0.0f}  //pad3
            });

    glGenBuffers(NumLightBuffers, LightBuffers);
    glBindBuffer(GL_UNIFORM_BUFFER, LightBuffers[LightBuffer]);
    glBufferData(GL_UNIFORM_BUFFER, Lights.size()*sizeof(LightProperties), Lights.data(), GL_STATIC_DRAW);
}

void build_materials( ) {
    // Brass
    Materials.push_back(
            {{0.33f, 0.22f, 0.03f, 1.0f}, //ambient
             {0.78f, 0.57f, 0.11f, 1.0f}, //diffuse
             {0.99f, 0.91f, 0.81f, 1.0f}, //specular
             27.8f, //shininess
             {0.0f, 0.0f, 0.0f}  //pad
            });
    // Red Plastic
    Materials.push_back(
            {{0.3f, 0.0f, 0.0f, 1.0f}, //ambient
             {0.6f, 0.0f, 0.0f, 1.0f}, //diffuse
             {0.8f, 0.6f, 0.6f, 1.0f}, //specular
             32.0f, //shininess
             {0.0f, 0.0f, 0.0f}  //pad
            });

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

        // TODO: Bind current texture id
        glBindTexture(GL_TEXTURE_2D, TextureIDs[i]);
        // TODO: Load image data into texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     image_data);
        // TODO: Generate mipmaps for texture
        glGenerateMipmap( GL_TEXTURE_2D );
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

    // a d rotate base
    if (key == GLFW_KEY_D)
    {
        theta += dtheta;
        if (theta > 360.0f)
        {
            theta -= 360.0f;
        }
        // TODO: Update base
        base.update_transform(rotate(theta, vec3(0.0f, 1.0f, 0.0f)));
    }
    else if (key == GLFW_KEY_A)
    {
        theta -= dtheta;
        if (theta < 0.0f)
        {
            theta += 360.0f;
        }
        // TODO: Update base
        base.update_transform(rotate(theta, vec3(0.0f, 1.0f, 0.0f)));
    }

    // w s rotates lower arm
    if (key == GLFW_KEY_S)
    {
        phi += dphi;
        if (phi > 90.0f)
        {
            phi = 90.0f;
        }
        // TODO: Update lower arm
        lower_arm.update_transform(translate(vec3(0.0f, BASE_HEIGHT, 0.0f))*rotate(phi, vec3(1.0f, 0.0f, 0.0f)));
    }
    else if (key == GLFW_KEY_W)
    {
        phi -= dphi;
        if (phi < -90.0f)
        {
            phi = -90.0f;
        }
        // TODO: Update lower arm
        lower_arm.update_transform(translate(vec3(0.0f, BASE_HEIGHT, 0.0f))*rotate(phi, vec3(1.0f, 0.0f, 0.0f)));
    }

    // m n rotates left upper arm
    if (key == GLFW_KEY_N)
    {
        left_psi += dpsi;
        if (left_psi > 180.0f)
        {
            left_psi = 180.0f;
        }
        // TODO: Update left upper arm
        left_upper_arm.update_transform(translate(vec3((LOWER_WIDTH+UPPER_WIDTH), 2*LOWER_HEIGHT, 0.0f))*rotate(left_psi, vec3(1.0f, 0.0f, 0.0f)));
    }
    else if (key == GLFW_KEY_M)
    {
        left_psi -= dpsi;
        if (left_psi < -180.0f)
        {
            left_psi = -180.0f;
        }
        // TODO: Update left upper arm
        left_upper_arm.update_transform(translate(vec3((LOWER_WIDTH+UPPER_WIDTH), 2*LOWER_HEIGHT, 0.0f))*rotate(left_psi, vec3(1.0f, 0.0f, 0.0f)));
    }

    // . , rotates right upper arm
    if (key == GLFW_KEY_COMMA)
    {
        right_psi += dpsi;
        if (right_psi > 180.0f)
        {
            right_psi = 180.0f;
        }
        // TODO: Update right upper arm
        right_upper_arm.update_transform(translate(vec3(-(LOWER_WIDTH+UPPER_WIDTH), 2*LOWER_HEIGHT, 0.0f))*rotate(right_psi, vec3(1.0f, 0.0f, 0.0f)));
    }
    else if (key == GLFW_KEY_PERIOD)
    {
        right_psi -= dpsi;
        if (right_psi < -180.0f)
        {
            right_psi = -180.0f;
        }
        // TODO: Update right upper arm
        right_upper_arm.update_transform(translate(vec3(-(LOWER_WIDTH+UPPER_WIDTH), 2*LOWER_HEIGHT, 0.0f))*rotate(right_psi, vec3(1.0f, 0.0f, 0.0f)));
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
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[obj][TexBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*texCoords*numVertices[obj], uvCoords.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

