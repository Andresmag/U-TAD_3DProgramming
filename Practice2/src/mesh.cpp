#include "../lib/mesh.h"
#include "../lib/buffer.h"
#include "../lib/material.h"
#include "../lib/state.h"

void Mesh::addBuffer(const std::shared_ptr<Buffer>& buffer, const Material& material)
{
    m_Buffers.push_back(new std::pair<std::shared_ptr<Buffer>, Material>(buffer, material));
}

size_t Mesh::getNumBuffers() const
{
    return m_Buffers.size();
}

const std::shared_ptr<Buffer>& Mesh::getBuffer(size_t index) const
{
    return m_Buffers.at(index)->first;
}

std::shared_ptr<Buffer>& Mesh::getBuffer(size_t index)
{
    return m_Buffers.at(index)->first;
}

const Material& Mesh::getMaterial(size_t index) const
{
    return m_Buffers.at(index)->second;
}

Material& Mesh::getMaterial(size_t index)
{
    return m_Buffers.at(index)->second;
}

void Mesh::draw()
{
    for (unsigned int idx = 0; idx < m_Buffers.size(); ++idx)
    {
        m_Buffers[idx]->second.prepare();
        m_Buffers[idx]->first->draw(*State::defaultShader);
    }
}
