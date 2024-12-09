#include "Model.h"

Model::Model() {
	//vertex buffer object (VBO)
	VBO = 0;

	//Vertex Array Object (VAO)
	VAO = 0;
}

Model::Model(const char mod[]) {
	//vertex buffer object (VBO)
	VBO = 0;

	//Vertex Array Object (VAO)
	VAO = 0;

	if (std::string(mod) == "bushes") {;
		setPoint(bushes, std::size(bushes));
	}
	else if (std::string(mod) == "gift") {
		setPoint(gift, std::size(gift));
	}
	else if (std::string(mod) == "sphere") {
		setPoint(sphere, std::size(sphere));
	}
	else if (std::string(mod) == "tree") {
		setPoint(tree, std::size(tree));
	}
	else if (std::string(mod) == "suzi_flat") {
		setPoint(suziFlat, std::size(suziFlat));
	}
	else if (std::string(mod) == "suzi_smooth") {
		setPoint(suziSmooth, std::size(suziSmooth));
	}
	else {
		triangles = -1;
	}
}

void Model::setPoint(float arr[], int size) {
	triangles = size/6;

	//vertex buffer object (VBO)
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, (4 * size), arr, GL_STATIC_DRAW); //(4 bites per element in array)

	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}

void Model::setPoint(const float arr[], int size) {
	triangles = size / 6;

	//vertex buffer object (VBO)
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, (4 * size), arr, GL_STATIC_DRAW); //(4 bites per element in array)

	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(const float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(const float), (GLvoid*)(3 * sizeof(float)));
}

void Model::setPoint() {
	float points[] = {
	0.0f, 0.5f, 0.0f, 0, 0, 1,
	0.5f, -0.5f, 0.0f, 0, 0, 1,
	-0.5f, -0.5f, 0.0f, 0, 0, 1
	};

	setPoint(points, 18);
}


int Model::drawModel() {
	if (triangles <= 0) {
		printf("MODEL IS EMPTY\n");
		return -1;
	}

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, triangles); //mode,first,count

	return 1;
}

