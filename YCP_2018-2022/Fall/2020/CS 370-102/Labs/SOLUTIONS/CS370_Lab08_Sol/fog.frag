#version 400 core
// TODO: Define input shader variable
in vec4 oColor;

// TODO: Define output shader variable
out vec4 fragColor;

// TODO: Define uniform shader variables
uniform vec4 fogColor;
uniform float fogStart;
uniform float fogEnd;


void main()
{
	// TODO: Compute fog factor
    float fog = (fogEnd - (gl_FragCoord.z/gl_FragCoord.w))/(fogEnd-fogStart);
    fog = clamp(fog, 0.0, 1.0);
    
    // TODO: Compute output color
    fragColor = mix(fogColor, oColor, fog);

}
