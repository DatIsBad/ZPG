#include "Model.h"

Model::Model() {
	//vertex buffer object (VBO)
	VBO = 0;

	//Vertex Array Object (VAO)
	VAO = 0;

	//vertex buffer object (VBO)
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO

	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float), (GLvoid*)(3 * sizeof(float)));

	// Unbind for safety
	glBindVertexArray(0);


	offModels = 7;
}

Model::~Model() {
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Model::addModel(const float arr[], int size) {
	this->setPoint(arr, size);
}

void Model::addModel(const char mod[]) {
	if (std::string(mod) == "bushes") {
		setPoint(0, bushes, std::size(bushes));
	}
	else if (std::string(mod) == "gift") {
		setPoint(1, gift, std::size(gift));
	}
	else if (std::string(mod) == "sphere") {
		setPoint(2, sphere, std::size(sphere));
	}
	else if (std::string(mod) == "tree") {
		setPoint(3, tree, std::size(tree));
	}
	else if (std::string(mod) == "suzi_flat") {
		setPoint(4, suziFlat, std::size(suziFlat));
	}
	else if (std::string(mod) == "suzi_smooth") {
		setPoint(5, suziSmooth, std::size(suziSmooth));
	}
}

void Model::setPoint(const float arr[], int size) {
	if (size <= 0) {
		printf("Error: elementCount must be positive.\n");
		return;
	}

	//record new data about model
	int count = size / 6;
	int offset = m_triangles.size() / 6;
	m_data.push_back({ offModels, offset , count });
	offModels = offModels + 1;

	//save model
	m_triangles.insert(m_triangles.end(), arr, arr + size);

	//add models into buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_triangles.size() * sizeof(float), m_triangles.data(), GL_STATIC_DRAW); //(4 bites per element in array)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::setPoint(int id, const float arr[], int size) {
	if (size <= 0) {
		printf("Error: elementCount must be positive.\n");
		return;
	}

	//record new data about model
	int count = size / 6;
	int offset = m_triangles.size() / 6;

	bool temp = false;
	for (int i = 0; i < m_data.size(); i++) {
		if (m_data[i].modelID == id) {
			temp = true;
			count = m_data[i].count;
			offset = m_data[i].offset;
			break;
		}
	}

	m_data.push_back({ id,  offset , count });

	if (temp == true) {
		return;
	}


	//save model
	m_triangles.insert(m_triangles.end(), arr, arr + size);

	//add models into buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_triangles.size() * sizeof(float), m_triangles.data(), GL_STATIC_DRAW); //(4 bites per element in array)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Model::drawModel(int id_model) {
	if (m_triangles.size() <= 0 || id_model < 0 || id_model >= m_data.size()) {
		printf("INVALID DRAW MODEL\n");
	}
		
	glDrawArrays(GL_TRIANGLES, m_data.at(id_model).offset, m_data.at(id_model).count ); //mode,first,count
}

void Model::drawModels() {
	if (m_triangles.size() <= 0) {
		printf("BUFFER IS EMPTY\n");
		return;
	}
	

	glBindVertexArray(VAO);
	for (int i = 0; i < m_triangles.size(); i++) {
		glDrawArrays(GL_TRIANGLES, m_data.at(i).offset, m_data.at(i).count); //mode,first,count
	}
}

void Model::bind() {
	glBindVertexArray(VAO);
}

void Model::unbind() {
	glBindVertexArray(0);
}

int Model::getmodelCount() {
	return m_data.size();
}