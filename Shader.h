#ifndef DEF_SHADER
#define DEF_SHADER


#include "common.h"
#include <string>

// Classe Shader

class Shader
{
public:

    Shader();
    Shader(Shader const &shaderACopier);
    Shader(const std::string& vertexSource, const std::string& fragmentSource);
    ~Shader();

    Shader& operator=(Shader const &shaderACopier);

    bool charger();
    GLuint getProgramID() const;

protected:

    static bool compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource);
    static std::string getGlError(const GLuint& id);
    void cleanup();

    GLuint m_vertexID;
    GLuint m_fragmentID;
    GLuint m_programID;

    std::string m_vertexSource;
    std::string m_fragmentSource;
};

#endif
