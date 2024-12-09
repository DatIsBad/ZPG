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
uniform vec3 cameraPos;
uniform vec3 cameraDir;

struct ModelInfo {
	vec3 Ra; // Ambient reflectance
	vec3 Rd; // Diffuse reflectance
	vec3 Rs; // Specular reflectance
	int haveTexture;
};
uniform sampler2D model_texture;
uniform ModelInfo model;

in vec4 worldPos;
in vec3 worldNorm;
in vec2 texPos;

out vec4 frag_colour;


void main() {
	vec3 modelColor = vec3(0.385f, 0.647f, 0.812f);
	vec3 fragPos = worldPos.xyz;
	vec3 norm = normalize(worldNorm);


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
		vec3 ambient;
		if (model.haveTexture == 1) {
			ambient = model.Ra * lights[i].ambientStrength * lights[i].lightColor * lights[i].lightIntensity * texture(model_texture, texPos).rgb;
		}
		else {
			ambient = model.Ra * lights[i].ambientStrength * lights[i].lightColor * lights[i].lightIntensity;
		}



		// cal diffuse
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse;
		if (model.haveTexture == 1) {
			diffuse = model.Rd * diff * lights[i].lightColor * lights[i].lightIntensity * texture(model_texture, texPos).rgb;
		}
		else {
			diffuse = model.Rd * diff * lights[i].lightColor * lights[i].lightIntensity;
		}

		// result
		finalColor += attenuation * (ambient + diffuse);
	}
	
	// result
	finalColor *= modelColor;
	frag_colour = vec4(finalColor, 1.0);
}

