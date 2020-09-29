#version 400 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vNormal;

uniform mat4 model_matrix;
uniform mat4 proj_matrix;
uniform mat4 cam_matrix;
uniform mat4 norm_matrix;

// Light structure
struct LightProperties {
    int type;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 position;
    vec3 direction;
    float spotCutoff;
    float spotExponent;
};

// Material structure
struct MaterialProperties {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

const int MaxLights = 8;
layout (std140) uniform LightBuffer {
    LightProperties Lights[MaxLights];
};

const int MaxMaterials = 8;
layout (std140) uniform MaterialBuffer {
    MaterialProperties Materials[MaxMaterials];
};

uniform int Material;
uniform vec3 EyePosition;

out vec3 oColor;

void main( )
{
    // Compute transformed vertex position in view space
    gl_Position = proj_matrix*(cam_matrix*(model_matrix*vPosition));

    // TODO: Compute l


    // TODO: Compute n (transformed by normal matrix)


    // TODO: Compute v (camera location - transformed vertex)


    // TODO: Compute half vector


    // Compute color
    vec3 rgb = vec3(0.0f);

    // TODO: Ambient term


    // TODO: Diffuse term (Lambert's law)


    if (diff != 0.0) {
        // TODO: Specular term


    }

    oColor = rgb;
}
