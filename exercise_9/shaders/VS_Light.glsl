#version 330
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;
layout(location = 2) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform int repeatTexture;

out vec4 worldPos;
out vec3 worldNorm;
out vec2 texPos;

void main() {
	worldPos = modelMatrix * vec4(vp, 1.0);
	mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
	worldNorm = normalize(normalMatrix * vn);
	texPos = uv * repeatTexture;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
};