#pragma once
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <iterator> // for std::size()
#include <string>
#include <vector>


#include"models/bushes.h"
#include"models/gift.h"
#include"models/sphere.h"
#include"models/suzi_flat.h"
#include"models/suzi_smooth.h"
#include"models/tree.h"
#include"models/plain.h"

class Model
{
public:
	Model();
	~Model();
	void addModel(const float arr[], int size);
	void addModel(const char mod[]);
	void drawModel(int id_model);
	void drawModels();
	void bind();
	void unbind();
	int getmodelCount();

private:
	void setPoint(const float arr[], int size);
	void setPoint(int id, const float arr[], int size);

	GLuint VBO;
	GLuint VAO;
	std::vector<float> m_triangles;

	int offModels;	// models that are not from addModel(const char mod[]);

	struct ModelMetadata {
		int modelID;	// id
		int offset;  // Offset in the vertex buffer (in vertices)
		int count;   // Number of vertices in the model
	};

	std::vector<ModelMetadata> m_data;
};

