#include "../lib/shader.h"
#include "../lib/vertex.h"
#include "../lib/glm/gtc/type_ptr.hpp"

uint32_t Shader::createShader(const char* shaderSource, EShaderType type)
{
    int retCode;
    uint32_t shader;
    if (type == EShaderType::ST_Vertex)
        shader = glCreateShader(GL_VERTEX_SHADER);
    else
        shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &retCode);
    if (retCode == GL_FALSE)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shader, sizeof(errorLog), nullptr, errorLog);
        m_Error = errorLog;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

void Shader::createProgram(uint32_t vertex, uint32_t fragment)
{
    GLint retCode;
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glGetProgramiv(m_ID, GL_LINK_STATUS, &retCode);
    if (retCode == GL_FALSE)
    {
        char errorLog[1024];
        glGetProgramInfoLog(m_ID, sizeof(errorLog), nullptr, errorLog);
        m_Error = errorLog;
        glDeleteProgram(m_ID);
        m_ID = 0;
    }
}

Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource)
    : m_Error(nullptr)
{
    // Create vertex shader
    uint32_t vertexShader = createShader(vertexShaderSource, EShaderType::ST_Vertex);
    if (m_Error)
        return;
    uint32_t fragmentShader = createShader(fragmentShaderSource, EShaderType::ST_Fragment);
    if (m_Error)
        return;

    createProgram(vertexShader, fragmentShader);
    if (m_Error)
        return;

    m_vposLoc = glGetAttribLocation(m_ID, "vertPos");
    m_vcolorLoc = glGetAttribLocation(m_ID, "vcolor"); // ??????
    m_vtextLoc = glGetAttribLocation(m_ID, "vertTex");
    m_vnormalLoc = glGetAttribLocation(m_ID, "vertNormal");
}

Shader::~Shader()
{
    glDeleteProgram(m_ID);
}

uint32_t Shader::getId() const
{
    return m_ID;
}

const char* Shader::getError() const
{
    return m_Error;
}

void Shader::use() const
{
    glUseProgram(m_ID);
}

void Shader::setupAttribs() const
{
    if (m_vposLoc != -1)
    {
        glEnableVertexAttribArray(m_vposLoc);
        glVertexAttribPointer(m_vposLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, m_Position)));

    }

    if (m_vcolorLoc != -1)
    {
        glEnableVertexAttribArray(m_vcolorLoc);
        glVertexAttribPointer(m_vcolorLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, m_Color)));

    }

    if (m_vtextLoc != -1)
    {
        glEnableVertexAttribArray(m_vtextLoc);
        glVertexAttribPointer(m_vtextLoc, 2, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, m_TextureCoord)));
    }

    if (m_vnormalLoc != -1)
    {
        glEnableVertexAttribArray(m_vnormalLoc);
        glVertexAttribPointer(m_vnormalLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, m_Normal)));
    }
}

int Shader::getLocation(const char* name) const
{
    return glGetUniformLocation(m_ID, name);
}

void Shader::setInt(int loc, int val)
{
    if (loc != -1)
        glUniform1i(loc, val);
}

void Shader::setFloat(int loc, float val)
{
    if (loc != -1)
        glUniform1f(loc, val);
}

void Shader::setVec3(int loc, const glm::vec3& vec)
{
    if (loc != -1)
        glUniform3f(loc, vec.x, vec.y, vec.z);
}

void Shader::setVec4(int loc, const glm::vec4& vec)
{
    if (loc != -1)
        glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
}

void Shader::setMatrix(int loc, const glm::mat4& matrix)
{
    if (loc != -1)
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}
