enum LightType {OFF, DIRECTIONAL, POINT, SPOT};

// Structure for lights
struct LightProperties {
	GLint type;
	GLfloat pad1[3];
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat position[4];
	GLfloat direction[3];
	GLfloat pad2;
	GLfloat spotCutoff;
	GLfloat spotExponent;
	GLfloat pad3[2];
};

struct MaterialProperties {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
	GLfloat pad[3];
};