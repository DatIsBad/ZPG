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
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));


	// Unbind for safety
	glBindVertexArray(0);


	offModels = 10;
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
		setPoint(0, 1, true, bushes, std::size(bushes));
	}
	else if (std::string(mod) == "gift") {
		setPoint(1, 0, true, gift, std::size(gift));
	}
	else if (std::string(mod) == "sphere") {
		setPoint(2, 0, true, sphere, std::size(sphere));
	}
	else if (std::string(mod) == "tree") {
		setPoint(3, 1, true, tree, std::size(tree));
	}
	else if (std::string(mod) == "suzi_flat") {
		setPoint(4, 2, true, suziFlat, std::size(suziFlat));
	}
	else if (std::string(mod) == "suzi_smooth") {
		setPoint(5, 2, true, suziSmooth, std::size(suziSmooth));
	}
	else if (std::string(mod) == "box_in") {
		setPoint(6, 0, false, box_in, std::size(box_in));
	}
	else if (std::string(mod) == "box_out") {
		setPoint(7, 0, false, box_out, std::size(box_out));
	}
	else if (std::string(mod) == "plain") {
		setPoint(8, 2, false, plain, std::size(plain));
	}
	
}

void Model::setPoint(const float arr[], int size) {
	if (size <= 0) {
		printf("Error: elementCount must be positive.\n");
		return;
	}

	//record new data about model
	int count = size / 8;
	int offset = m_triangles.size() / 8;
	m_data.push_back({ offModels, offset , count, rand()%Material::getMaterialCount()});
	offModels = offModels + 1;

	//save model
	m_triangles.insert(m_triangles.end(), arr, arr + size);

	//add models into buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_triangles.size() * sizeof(float), m_triangles.data(), GL_STATIC_DRAW); //(4 bites per element in array)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::setPoint(int id, int material, bool convert, const float arr[], int size) {
	if (size <= 0) {
		printf("Error: elementCount must be positive.\n");
		return;
	}

	//record new data about model
	int count = 0;
	if (convert == true) {
		count = size / 6;
	}
	else {
		count = size / 8;
	}
	
	int offset = m_triangles.size() / 8;

	bool temp = false;
	for (int i = 0; i < m_data.size(); i++) {
		if (m_data[i].modelID == id) {
			temp = true;
			count = m_data[i].count;
			offset = m_data[i].offset;
			break;
		}
	}

	m_data.push_back({ id,  offset , count, material });

	if (temp == true) {
		return;
	}


	//save model
	if (convert == true) {
		SixToEight(arr, size);
	}
	else {
		m_triangles.insert(m_triangles.end(), arr, arr + size);
	}
	

	//add models into buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_triangles.size() * sizeof(float), m_triangles.data(), GL_STATIC_DRAW); //(4 bites per element in array)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Model::SixToEight(const float arr[], int size) {
	for (int i = 0; i < size / 6; i++) {
		m_triangles.push_back(arr[i * 6]);
		m_triangles.push_back(arr[i * 6 + 1]);
		m_triangles.push_back(arr[i * 6 + 2]);
		m_triangles.push_back(arr[i * 6 + 3]);
		m_triangles.push_back(arr[i * 6 + 4]);
		m_triangles.push_back(arr[i * 6 + 5]);
		m_triangles.push_back(0.0f);
		m_triangles.push_back(0.0f);
	}
}

void Model::loadModel(std::string filePath) {
	Assimp::Importer importer;

	// Load the .obj file
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate 
		| aiProcess_OptimizeMeshes              
		| aiProcess_JoinIdenticalVertices);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		throw std::runtime_error(std::string("Assimp Error: ") + importer.GetErrorString());
	}

	int count = 0;
	int offset = m_triangles.size() / 8;
	std::vector<Vertex> vertices;


	for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
		aiMesh* mesh = scene->mMeshes[meshIndex];

		// Extract triangles from the mesh
		for (unsigned int faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
			const aiFace& face = mesh->mFaces[faceIndex];

			// Ensure the face is a triangle
			if (face.mNumIndices != 3) {
				std::cerr << "Non-triangle face detected, skipping." << std::endl;
				continue;
			}

			// Extract the data for each vertex in the triangle
			for (int i = 0; i < 3; ++i) { // Loop over the 3 vertices of the triangle
				unsigned int vertexIndex = face.mIndices[i];
				count++;
				// Position
				m_triangles.push_back(mesh->mVertices[vertexIndex].x);
				m_triangles.push_back(mesh->mVertices[vertexIndex].y);
				m_triangles.push_back(mesh->mVertices[vertexIndex].z);

				// Normal
				if (mesh->HasNormals()) {
					m_triangles.push_back(mesh->mNormals[vertexIndex].x);
					m_triangles.push_back(mesh->mNormals[vertexIndex].y);
					m_triangles.push_back(mesh->mNormals[vertexIndex].z);
				}
				else {
					m_triangles.push_back(0.0f); // Default normal
					m_triangles.push_back(0.0f);
					m_triangles.push_back(0.0f);
				}

				// Texture Coordinates (UV)
				if (mesh->HasTextureCoords(0)) {
					m_triangles.push_back(mesh->mTextureCoords[0][vertexIndex].x);
					m_triangles.push_back(mesh->mTextureCoords[0][vertexIndex].y);
				}
				else {
					m_triangles.push_back(0.0f); // Default UV
					m_triangles.push_back(0.0f);
				}
			}
		}
	}



	m_data.push_back({ offModels, offset , count, rand() % Material::getMaterialCount() });
	offModels++;


	bind();
	//add models into buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_triangles.size() * sizeof(float), m_triangles.data(), GL_STATIC_DRAW); //(4 bites per element in array)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	unbind();



}















void Model::assignTexture(int id_model, std::string textureName, int textureMultiplier) {
	m_data.at(id_model).textureName = textureName;
	m_data.at(id_model).haveTexture = 1;
	m_data.at(id_model).textureMultiplier = textureMultiplier;
}


void Model::drawModel(int id_model, ShaderProgram* sh, TextureManager* tm) {
	if (m_triangles.size() <= 0 || id_model < 0 || id_model >= m_data.size()) {
		printf("INVALID DRAW MODEL\n");
	}
	Material::getMaterial(sh, m_data.at(id_model).material);
	sh->useHaveTexture(m_data.at(id_model).haveTexture);

	if (m_data.at(id_model).haveTexture == 1) {
		tm->bindTexture(m_data.at(id_model).textureName);
		if (tm->getType(m_data.at(id_model).textureName) == GL_TEXTURE_2D) {
			sh->useTexture(tm->getTextureUnit(m_data.at(id_model).textureName), m_data.at(id_model).textureMultiplier);
		}
		else if (tm->getType(m_data.at(id_model).textureName) == GL_TEXTURE_CUBE_MAP) {
			sh->useCubeMap(tm->getTextureUnit(m_data.at(id_model).textureName));
		}
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