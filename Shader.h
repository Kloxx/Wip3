#ifndef DEF_SHADER
#define DEF_SHADER


#include "common.h"
#include <string>

// Classe Shader

class Shader
{
public:

    Shader();
    Shader(const std::string& vertexSource, const std::string& fragmentSource);
    ~Shader();

    void setUniform(const std::string& name, const glm::mat4& value) const;
    void setUniform(const std::string& name, const float& value) const;
    GLuint getProgramID() const;

protected:

    static bool compileShader(GLuint &shader, GLenum type, std::string const &fichierSource);
    static std::string getGlError(const GLuint& id);
    bool load();
    void cleanup();

    GLuint m_vertexID;
    GLuint m_fragmentID;
    GLuint m_programID;

    std::string m_vertexSource;
    std::string m_fragmentSource;
};

#endif
