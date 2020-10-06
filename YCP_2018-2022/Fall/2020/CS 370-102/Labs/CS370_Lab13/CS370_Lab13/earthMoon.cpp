#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"	// Sean Barrett's image loader - http://nothings.org/
#include <stdio.h>
#include <vector>
#include "vgl.h"
#include "objloader.h"
#include "utils.h"
#include "vmath.h"

using namespace vmath;
using namespace std;

enum VAO_IDs {Background, Sphere, NumVAOs};
enum ObjBuffer_IDs {PosBuffer, TexBuffer, NumObjBuffers};
enum Textures {Earth, Moon, Space, NumTextures};

GLuint VAOs[NumVAOs];
GLuint ObjBuffers[NumVAOs][NumObjBuffers];
GLuint TextureIDs[NumTextures];

GLint numVertices[NumVAOs];
GLint posCoords = 4;
GLint texCoords = 2;

vector<const char *> objFiles = {"","../models/uv_sphere.obj"};
vector<const char *> texFiles = {"../textures/earth.bmp", "../textures/moon.bmp", "../textures/space.jpg"};
// Camera
vec3 eye = {0.0f, 0.0f, 4.0f};
vec3 center = {0.0f, 0.0f, 0.0f};
vec3 up = {0.0f, 1.0f, 0.0f};

// Shader variables
GLuint program;
GLuint vPos;
GLuint vTex;
GLuint camera_mat_loc;
GLuint model_mat_loc;
GLuint proj_mat_loc;
GLuint eye_loc;
const char *vertex_shader = "../basicTex.vert";
const char *frag_shader = "../basicTex.frag";

// Global state
mat4 proj_matrix;
mat4 model_matrix;
mat4 camera_matrix;
GLfloat cube_angle = 0.0;
GLdouble elTime = 0.0;
GLdouble rpm = 10.0;
vec3 axis = {0.0f, 1.0f, 0.0f};

// Global screen dimensions
GLint ww,hh;

void build_geometry( );
void build_textures();
void display( );
void render_scene( );
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, int button, int action, int mods);
void draw_background();
void load_object(GLuint obj);
void draw_object(GLuint obj);

int main(int argc, char**argv)
{
	// Create OpenGL window
	GLFWwindow* window = CreateWindow("Earth Moon");
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
    // Create textures
    build_textures();
    
    // Load shaders
	ShaderInfo shaders[] = { {GL_VERTEX_SHADER, vertex_shader},{GL_FRAGMENT_SHADER, frag_shader},{GL_NONE, NULL} };
	program = LoadShaders(shaders);

	// Select shader program and associate shader variables
	vPos = glGetAttribLocation(program, "vPosition");
    vTex = glGetAttribLocation(program, "vTexCoord");
    camera_mat_loc = glGetUniformLocation(program, "cam_matrix");
    model_mat_loc = glGetUniformLocation(program, "model_matrix");
    proj_mat_loc = glGetUniformLocation(program, "proj_matrix");

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

    load_object(Sphere);

    // Create background quad
    vector<vec4> vertices;
    vector<vec2> uvCoords;

    vertices.push_back(vec4(1.0f, 1.0f, 0.0f, 1.0f));
    vertices.push_back(vec4(-1.0f, 1.0f, 0.0f, 1.0f));
    vertices.push_back(vec4(-1.0f, -1.0f, 0.0f, 1.0f));
    vertices.push_back(vec4(-1.0f, -1.0f, 0.0f, 1.0f));
    vertices.push_back(vec4(1.0f, -1.0f, 0.0f, 1.0f));
    vertices.push_back(vec4(1.0f, 1.0f, 0.0f, 1.0f));

    // TODO: Define texture coordinates


    numVertices[Background] = vertices.size();

    glBindVertexArray(VAOs[Background]);
    glGenBuffers(NumObjBuffers, ObjBuffers[Background]);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[Background][PosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*posCoords*numVertices[Background], vertices.data(), GL_STATIC_DRAW);
    // Bind texture coordinate buffer and load data
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[Background][TexBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*texCoords*numVertices[Background], uvCoords.data(), GL_STATIC_DRAW);

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

        // TODO: Load image data into texture

        // TODO: Generate mipmaps for texture

        // TODO: Set scaling modes

        // TODO: Set wrapping modes


        // Set maximum anisotropic filtering for system
        GLfloat max_aniso = 0.0f;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso);
        // set the maximum!
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso);
    }
}

void display( )
{
    proj_matrix = mat4().identity();
    camera_matrix = mat4().identity();

	// Clear window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render background
	draw_background();

    // Set anisotropic scale factors
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
	mat4 rot2_matrix;

    // Select shader program
    glUseProgram(program);
    // Pass projection matrix to shader
    glUniformMatrix4fv(proj_mat_loc, 1, GL_FALSE, proj_matrix);
    // Pass camera matrix to shader
    glUniformMatrix4fv(camera_mat_loc, 1, GL_FALSE, camera_matrix);

    // Draw earth
    trans_matrix = translation(0.0f, 0.0f, 0.0f);
    rot_matrix = rotation(cube_angle, normalize(axis));
    scale_matrix = scale(1.0f, 1.0f, 1.0f);
    model_matrix = trans_matrix*rot_matrix*scale_matrix;
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    // TODO: Bind earth texture id

    draw_object(Sphere);

    // Draw moon
    rot_matrix = rotation(cube_angle, normalize(axis));
    scale_matrix = scale(0.25f, 0.25f, 0.25f);
    trans_matrix = translation(2.0f, 0.0f, 0.0f);
    model_matrix = rot_matrix*trans_matrix*rot_matrix*scale_matrix;
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    // TODO: Bind moon texture id

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
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[obj][TexBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*texCoords*numVertices[obj], uvCoords.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void draw_background(){
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


    // TODO: Set default camera matrix

    // Select shader program
    glUseProgram(program);
    // Pass projection matrix to shader
    glUniformMatrix4fv(proj_mat_loc, 1, GL_FALSE, proj_matrix);
    // Pass camera matrix to shader
    glUniformMatrix4fv(camera_mat_loc, 1, GL_FALSE, camera_matrix);
    // TODO: Set default model matrix

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glBindVertexArray(VAOs[Background]);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[Background][PosBuffer]);
    glVertexAttribPointer(vPos, posCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vPos);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[Background][TexBuffer]);
    glVertexAttribPointer(vTex, texCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vTex);
    // TODO: Bind background texture id

	// TODO: Draw background with depth buffer writes disabled

    glDrawArrays(GL_TRIANGLES, 0, numVertices[Background]);

}

void draw_object(GLuint obj){
    glBindVertexArray(VAOs[obj]);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[obj][PosBuffer]);
    glVertexAttribPointer(vPos, posCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vPos);
    glBindBuffer(GL_ARRAY_BUFFER, ObjBuffers[obj][TexBuffer]);
    glVertexAttribPointer(vTex, texCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vTex);
    glDrawArrays(GL_TRIANGLES, 0, numVertices[obj]);

}
