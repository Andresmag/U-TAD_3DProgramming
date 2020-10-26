#pragma once
#include <memory>
#include "glm/vec2.hpp"

#include "../lib/stb_image.h"

class Texture
{
    uint32_t m_ID;
    glm::ivec2 m_Size;

public:
    Texture(uint32_t id, glm::ivec2 size);
    static std::shared_ptr<Texture> load(const char* filename);
    uint32_t getId() const;
    const glm::ivec2& getSize() const;
    void bind() const;
};
