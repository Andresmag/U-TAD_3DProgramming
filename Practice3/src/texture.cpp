#include "../lib/texture.h"
#include "GL/glew.h"

Texture::Texture(uint32_t id, glm::ivec2 size)
    : m_ID(id)
    , m_Size(size)
{
}

std::shared_ptr<Texture> Texture::load(const char* filename)
{
    int width, height;
    stbi_set_flip_vertically_on_load(true); // Change pixels row order upside down
    unsigned char* bytesTexture = stbi_load(filename, &width, &height, nullptr, 4);
    if (bytesTexture)
    {
        // OpenGL texture
        // Generate 
        GLuint texId;
        glGenTextures(1, &texId);

        // Activation
        glBindTexture(GL_TEXTURE_2D, texId);

        // Setting params
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        // Load image
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytesTexture);

        // Mipmaps generation
        glGenerateMipmap(GL_TEXTURE_2D);

        // Delete buffer
        stbi_image_free(bytesTexture);

        return std::make_shared<Texture>(texId, glm::ivec2(width, height));
    }

    return nullptr;
}

uint32_t Texture::getId() const
{
    return m_ID;
}

const glm::ivec2& Texture::getSize() const
{
    return m_Size;
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_ID);
}
