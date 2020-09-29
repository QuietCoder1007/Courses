#version 400 core
// TODO: Define uniform shader variables
uniform mat4 model_matrix;
uniform mat4 proj_matrix;
uniform mat4 camera_matrix;
uniform vec4 vColor;

// TODO: Define attribute shader in layout
layout(location=0) in vec4 vPosition;

// TODO: Define output shader variables
out vec4 oColor;

void main()
{
    // TODO: Perform shader operations
    gl_Position = proj_matrix*model_matrix*camera_matrix*vPosition;
    oColor = vColor;
}
