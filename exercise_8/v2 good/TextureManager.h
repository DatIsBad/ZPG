#pragma once
#include <vector>
#include "Textures.h"
class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void loadTexture(const std::string& name, const std::string& filePath);
	void loadCubeMap(const std::string& name, int type);
	void loadCubeMap(const std::string& name, const std::vector<std::string>& facePaths);



	void bindTexture(const std::string& name);
	void bindTexture(GLuint unit);
	void unbindAll();
	GLuint getTextureUnit(const std::string& name);
	
	std::vector<std::string> getTextureNames();
	
	
	int getSize() { return m_textures.size(); }
	int getType(const std::string& name);

	void unloadAllTextures();


private:
	struct MT_data {
		std::string name;	// Unique identifier for the texture (e.g., file path)
		Textures* texture;  // Pointer to the actual texture
		GLuint unit;		// Automatically assigned texture unit
		int type;			// used for GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP...
	};

	std::vector<MT_data> m_textures;
	GLuint m_nextAvailableUnit;

};

