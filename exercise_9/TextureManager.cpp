#include "TextureManager.h"


TextureManager::TextureManager() {
    m_nextAvailableUnit = 0;
}

// Private destructor to clean up textures
TextureManager::~TextureManager() {
    for (auto& entry : m_textures) {
        delete entry.texture;
    }
    m_textures.clear();
}



//-----------------------------------------------------------------------------------------------------------
void TextureManager::loadTexture(const std::string& name, const std::string& filePath) {
    glActiveTexture(m_nextAvailableUnit);
        for (const auto& entry : m_textures) {
        if (entry.name == name) {
            return; // Texture already loaded
        }
    }

    Textures* newTexture = new Textures();
    if (!newTexture->loadFromFile(filePath)) {
        delete newTexture;
        printf("Failed to load texture\n");
        exit(1);
    }

    if (m_nextAvailableUnit >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {
        delete newTexture;
        printf("Exceeded maximum texture units");
        exit(2);
    }

    m_textures.push_back({ name, newTexture, m_nextAvailableUnit++ , GL_TEXTURE_2D });
}




void TextureManager::loadCubeMap(const std::string& name, int type) {
    glActiveTexture(m_nextAvailableUnit);
    for (const auto& entry : m_textures) {
        if (entry.name == name) {
            return; // Texture already loaded
        }
    }

    Textures* newTexture = new Textures();
    if (!newTexture->loadCubeMap(type)) {
        delete newTexture;
        printf("Failed to load cubeMap %d\n", type);
        exit(1);
    }

    if (m_nextAvailableUnit >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {
        delete newTexture;
        printf("Exceeded maximum texture units");
        exit(2);
    }

    m_textures.push_back({ name, newTexture, m_nextAvailableUnit++ , GL_TEXTURE_CUBE_MAP });
}




void TextureManager::loadCubeMap(const std::string& name, const std::vector<std::string>& facePaths) {
    glActiveTexture(m_nextAvailableUnit);
    for (const auto& entry : m_textures) {
        if (entry.name == name) {
            return; // Texture already loaded
        }
    }

    Textures* newTexture = new Textures();
    if (!newTexture->loadCubeMap(facePaths)) {
        delete newTexture;
        printf("Failed to load cubeMap\n");
        exit(1);
    }

    if (m_nextAvailableUnit >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {
        delete newTexture;
        printf("Exceeded maximum texture units");
        exit(2);
    }

    m_textures.push_back({ name, newTexture, m_nextAvailableUnit++ , GL_TEXTURE_CUBE_MAP });
}




//-----------------------------------------------------------------------------------------------------------
void TextureManager::bindTexture(const std::string& name) {
    for (const auto& entry : m_textures) {
        if (entry.name == name) {
            entry.texture->bind(entry.unit, entry.type);
            return;
        }
    }

    printf("COULDNT FIND TEXTURE\n");
}


void TextureManager::bindTexture(GLuint unit) {
    for (const auto& entry : m_textures) {
        if (entry.unit == unit) {
            entry.texture->bind(entry.unit, entry.type);
            return;
        }
    }

    printf("COULDNT FIND TEXTURE\n");
}


void TextureManager::unbindAll() {
    for (const auto& entry : m_textures) {
        glActiveTexture(GL_TEXTURE0 + entry.unit);
        glBindTexture(entry.type, 0);
    }
}


// Retrieve the texture unit assigned to a specific texture
GLuint TextureManager::getTextureUnit(const std::string& name)  {
    for (const auto& entry : m_textures) {
        if (entry.name == name) {
            return entry.unit;
        }
    }

    return -1;
}


std::vector<std::string> TextureManager::getTextureNames()  {
    std::vector<std::string> textureNames;
    for (const auto& entry : m_textures) {
        textureNames.push_back(entry.name);
    }
    return textureNames;
}


int TextureManager::getType(const std::string& name) {
    for (const auto& entry : m_textures) {
        if (entry.name == name) {
            return entry.type;
        }
    }

    return -1;
}









void TextureManager::unloadAllTextures() {
    for (auto& entry : m_textures) {
        delete entry.texture;        // Free GPU memory
    }
    m_textures.clear();
    m_nextAvailableUnit = 0;           // Reset texture unit tracking
}