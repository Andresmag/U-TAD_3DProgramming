#pragma once

#include "glm/glm.hpp"

struct Vertex
{
    glm::vec3 m_Position;
    glm::vec3 m_Color;
    glm::vec2 m_TextureCoord;
    glm::vec3 m_Normal;

    Vertex()
        : m_Position(0, 0, 0)
        , m_Color(0, 0, 0)
        , m_TextureCoord(0, 0)
        , m_Normal(0, 0, 0)
    {}

    Vertex(glm::vec3 value, glm::vec3 color, glm::vec2 textCoord, glm::vec3 normal)
        : m_Position(value)
        , m_Color(color)
        , m_TextureCoord(textCoord)
        , m_Normal(normal)
    {}
};