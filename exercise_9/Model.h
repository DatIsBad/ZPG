#pragma once
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

#include <iterator> // for std::size()
#include <string>
#include <vector>

#include "ShaderProgram.h"
#include "Material.h"
#include "TextureManager.h"

#include"models/bushes.h"
#include"models/gift.h"
#include"models/sphere.h"
#include"models/suzi_flat.h"
#include"models/suzi_smooth.h"
#include"models/tree.h"
#include"models/plain.h"
#include"models/myModels.h"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>





class Model
{
public:
	Model();
	~Model();
	void addModel(const float arr[], int size);
	void addModel(const char mod[]);
	void loadModel(std::string filePath);

	void drawModel(int id_model, ShaderProgram* sh, TextureManager* tm);
	void assignTexture(int id_model, std::string textureName, int textureMultiplier);
	void drawModels();
	void bind();
	void unbind();
	int getmodelCount();
	


private:
	void setPoint(const float arr[], int size);
	void setPoint(int id, int material, bool convert, const float arr[], int size);
	void SixToEight(const float arr[], int size);
	

	GLuint VBO;
	GLuint VAO;


	std::vector<float> m_triangles;

	int offModels;	// models that are not from addModel(const char mod[]);

	struct ModelMetadata {
		int modelID;	// id
		int offset;  // Offset in the vertex buffer (in vertices)
		int count;   // Number of vertices in the model
		int material;
		int haveTexture = -1;
		std::string textureName;
		int textureMultiplier = 1;
	};

	struct Vertex {
		float position[3]; // x, y, z
		float normal[3];   // nx, ny, nz
		float uv[2];       // u, v
	};


	std::vector<ModelMetadata> m_data;
};

