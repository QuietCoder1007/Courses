#version 400 core
uniform mat4 model_matrix;
uniform vec3 color;

layout(location = 0) in vec4 vPosition;

out vec4 oColor;

void main()
{
    gl_Position = model_matrix*vPosition;
    oColor = vec4(color,1.0);
}
