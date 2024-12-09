#include "Textures.h"
Textures::Textures() {
	m_textureID = 0;
	m_width = 0;
	m_height = 0;
	m_isCubeMap = false;
}

Textures::~Textures() {
	if (m_textureID) {
		glDeleteTextures(1, &m_textureID);
	}
}


bool Textures::loadFromFile(std::string path){
	m_filepath = path;
	m_textureID = SOIL_load_OGL_texture(
		path.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
	);

	if (m_textureID == 0) {
		return false; // Failed to load texture
	}
	m_isCubeMap = false;

	// Retrieve texture dimensions
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	
	
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &m_width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &m_height);
	
	
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}



bool Textures::loadCubeMap( int type) {
	//Bind the first texture to the first texture unit.
	//Cube Map (SkyBox)
	if (type == 0) {
		m_textureID = SOIL_load_OGL_cubemap("textures/skybox1/1.jpg", "textures/skybox1/2.jpg", "textures/skybox1/3.jpg", 
			"textures/skybox1/4.jpg", "textures/skybox1/5.jpg", "textures/skybox1/6.jpg",
			SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	}
		 
	else if (type == 1) {
		m_textureID = SOIL_load_OGL_cubemap("textures/skybox2/1.png", "textures/skybox2/2.png", "textures/skybox2/3.png", 
			"textures/skybox2/4.png", "textures/skybox2/5.png", "textures/skybox2/6.png", 
			SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	}


	if (m_textureID == 0) {
		return false; // Failed to load texture
	}
	m_isCubeMap = true;


	// Retrieve dimensions from one face (all faces must have the same size)
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &m_width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &m_height);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return true;
}



bool Textures::loadCubeMap(const std::vector<std::string>& facePaths) {
	m_textureID = SOIL_load_OGL_cubemap(
		facePaths[0].c_str(), facePaths[1].c_str(), facePaths[2].c_str(),
		facePaths[3].c_str(), facePaths[4].c_str(), facePaths[5].c_str(),
		SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS
	);

	if (m_textureID == 0) {
		return false; // Failed to load texture
	}
	m_isCubeMap = true;


	// Retrieve dimensions from one face (all faces must have the same size)
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &m_width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &m_height);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return true;
}







void Textures::bind(GLuint unit, int type) {
	if (m_textureID == 0) {
		return; // Failed to load texture
	}
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(type, m_textureID);
}

void Textures::unbind(int type) {
	glBindTexture(type, 0);
}