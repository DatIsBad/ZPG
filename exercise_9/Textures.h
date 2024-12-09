#pragma once
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <string>
#include <vector>



class Textures
{
public:
	Textures();
	~Textures();


	void bind(GLuint unit,int type);
	void unbind(int type);


	bool loadFromFile(std::string path);
	bool loadCubeMap(int type);
	bool loadCubeMap(const std::vector<std::string>& facePaths);









	int getWidth()  { return m_width; }
	int getHeight()  { return m_height; }
	bool isCubeMapTexture()  { return m_isCubeMap; }


private:
	



	GLuint m_textureID;
	std::string m_filepath;
	int m_width, m_height;
	bool m_isCubeMap;

};

