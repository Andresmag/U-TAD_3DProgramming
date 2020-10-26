#include "../lib/buffer.h"
#include "GL/glew.h"
#include "../lib/vertex.h"
#include "../lib/shader.h"

Buffer::Buffer(std::vector<Vertex> vertices, std::vector<uint16_t> indices)
{
    glGenBuffers(2, m_IDs.data());
    glBindBuffer(GL_ARRAY_BUFFER, m_IDs[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IDs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indices.size(), indices.data(), GL_STATIC_DRAW);
    m_NumIndices = indices.size();
}

void Buffer::draw(const Shader& shader) const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_IDs[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IDs[1]);
    shader.setupAttribs();
    glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_SHORT, nullptr);
}
