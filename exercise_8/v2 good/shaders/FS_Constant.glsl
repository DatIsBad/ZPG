#version 330


struct ModelInfo {
	vec3 Ra; // Ambient reflectance
	vec3 Rd; // Diffuse reflectance
	vec3 Rs; // Specular reflectance
	int haveTexture;
};

uniform ModelInfo model;

out vec4 frag_colour;
in vec3 color;
in vec2 texPos;
uniform vec3 colorConstant;
uniform sampler2D model_texture;

void main() {
	if (model.haveTexture == 1) {
		frag_colour = vec4(texture(model_texture, texPos).rgb, 1.0);
	}
	else {
		frag_colour = vec4(colorConstant, 1.0);
	}
	
};