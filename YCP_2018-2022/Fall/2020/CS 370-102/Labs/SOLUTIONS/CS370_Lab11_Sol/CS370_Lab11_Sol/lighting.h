#include "vmath.h"

enum LightType {OFF, DIRECTIONAL, POINT, SPOT};

// Structure for lights
struct LightProperties {
	GLint type;
	GLfloat pad1[3];
	vmath::vec4 ambient;
	vmath::vec4 diffuse;
	vmath::vec4 specular;
	vmath::vec4 position;
	vmath::vec3 direction;
	GLfloat pad2;
	GLfloat spotCutoff;
	GLfloat spotExponent;
	GLfloat pad3[2];
};

struct MaterialProperties {
	vmath::vec4 ambient;
	vmath::vec4 diffuse;
	vmath::vec4 specular;
	GLfloat shininess;
	GLfloat pad[3];
};