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

	int type;              // Light type: 1 = point, 2 = cone, 3 = directional
	vec3 lightDir;         // Light direction for cone and directional lights
	float innerCutoff;     // Inner cutoff for cone light
	float outerCutoff;     // Outer cutoff for cone light
	bool enabled;			// if the light should be currently active
	bool isCamera;         // Whether this light is attached to the camera
};

#define MAX_LIGHTS 50 // Maximum number of lights supported
uniform Light lights[MAX_LIGHTS];
uniform int numLights; // Number of active lights

in vec4 worldPos;
in vec3 worldNorm;
uniform vec3 cameraPos;
uniform vec3 cameraDir;

out vec4 frag_colour;
void main() {
	vec3 modelColor = vec3(0.385, 0.647, 0.812);
	vec3 fragPos = worldPos.xyz;
	vec3 norm = normalize(worldNorm);
	vec3 viewDir = normalize(cameraPos - fragPos);

	vec3 finalColor = vec3(0.0);

	for (int i = 0; i < numLights; i++) {
		vec3 lightPos = lights[i].lightPos;
		vec3 lightDir = lights[i].lightDir;

		// Adjust light to camera if isCamera is true
		if (lights[i].isCamera) {
			lightPos = cameraPos;
		}
	
		vec3 temp = lightPos - fragPos;
		float distance = length(temp);

		// Skip light if outside range
		if ((lights[i].type != 3 && distance > lights[i].range) || lights[i].enabled == false) continue;

		float attenuation = 1.0f;



		if (lights[i].type == 1) { // point light
			lightDir = normalize(temp);
			attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));
		}
		else if (lights[i].type == 2) { // Cone light
			lightDir = normalize(temp);

			float theta = dot(lightDir, normalize(-lights[i].lightDir));

			if (lights[i].isCamera) {
				theta = dot(lightDir, normalize(-cameraDir));
			}

			if (theta > lights[i].outerCutoff) {
				float epsilon = lights[i].innerCutoff - lights[i].outerCutoff;
				float intensity = clamp((theta - lights[i].outerCutoff) / epsilon, 0.0, 1.0);
				attenuation = intensity / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));
			}
			else {
				continue; // Skip fragments outside the cone
			}
		}
		else if (lights[i].type == 3) { // Directional light
			lightDir = normalize(-lights[i].lightDir); // Fixed direction
		}



		// Ambient component
		vec3 ambient = lights[i].ambientStrength * lights[i].lightColor * lights[i].lightIntensity;

		// Diffuse component
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lights[i].lightColor * lights[i].lightIntensity;

		// Specular component
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
		vec3 specular = lights[i].specularStrength * spec * lights[i].lightColor * lights[i].lightIntensity;

		

		// result
		finalColor += attenuation * (ambient + diffuse + specular);
	}
	finalColor *= modelColor;
	frag_colour = vec4(finalColor, 1.0f);
}