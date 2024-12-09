#version 330

in vec3 position;   

out vec4 FragColor;   // Output fragment color

uniform samplerCube uCubeMap; // Cube map sampler

void main() {
    // Output the cube map color
    FragColor = texture(uCubeMap, position);
}