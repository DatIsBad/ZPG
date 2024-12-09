#version 330

out vec4 frag_colour;
in vec3 color;
uniform vec3 colorConstant;

void main() {
	frag_colour = vec4(colorConstant, 1.0);
};