#version 330

struct Light {
	vec3 lightPos;
	vec3 lightColor;
	float lightIntensity;
	float ambientStrength;
	float specularStrength;

	float constant;		// Constant attenuation (range of unafection)
	float linear;		// Linear attenuation
	float quadratic;	// Quadratic attenuation
	float range;		// Light cutoff range
};

#define MAX_LIGHTS 50 // Maximum number of lights supported
uniform Light lights[MAX_LIGHTS];
uniform int numLights; // Number of active lights

in vec4 worldPos;
in vec3 worldNorm;
out vec4 frag_colour;


void main() {
	vec3 modelColor = vec3(0.385f, 0.647f, 0.812f);
	vec3 fragPos = worldPos.xyz;
	vec3 norm = normalize(worldNorm);


	vec3 finalColor = vec3(0.0);

	for (int i = 0; i < numLights; i++) {
		// Ambient component
		vec3 ambient = lights[i].ambientStrength * lights[i].lightColor * lights[i].lightIntensity;

		// cal diffuse
		vec3 lightDir = normalize(lights[i].lightPos - fragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lights[i].lightColor * lights[i].lightIntensity;


		vec3 temp = lights[i].lightPos - fragPos;
		float distance = length(temp);
		// Skip light if outside range
		if (distance > lights[i].range) continue;

		// Calculate attenuation
		float attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));

		// result
		finalColor += attenuation * (ambient + diffuse);
	}
	
	// result
	finalColor *= modelColor;
	frag_colour = vec4(finalColor, 1.0);
}

