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
    vec3 LightDirection = -normalize(Lights[0].direction);

    // TODO: Compute n (transformed by normal matrix)
    vec3 Normal = vec3(normalize(norm_matrix * normalize(vec4(vNormal,0.0f))));

    // TODO: Compute v (camera location - transformed vertex)
    vec4 Position = model_matrix*vPosition;
    vec3 View = normalize(EyePosition - Position.xyz);

    // TODO: Compute half vector
    vec3 HalfVector = normalize(LightDirection + View);

    // Compute color
    vec3 rgb = vec3(0.0f);

    // TODO: Ambient term
    rgb += vec3(Lights[0].ambient*Materials[Material].ambient);

    // TODO: Diffuse term (Lambert's law)
    float diff = max(0.0f, dot(Normal, LightDirection));
    rgb += diff*vec3(Lights[0].diffuse*Materials[Material].diffuse);

    if (diff != 0.0) {
        // TODO: Specular term
        float spec = pow(max(0.0f, dot(Normal, HalfVector)),Materials[Material].shininess);
        rgb += spec*vec3(Lights[0].specular*Materials[Material].specular);
    }

    oColor = rgb;
}
