#include "Shader.h"

// Includes communs
#include <iostream>
#include <fstream>
#include <cassert>

// Constructeurs et Destructeur

Shader::Shader() :
    m_vertexID(0),
    m_fragmentID(0),
    m_programID(0),
    m_vertexSource(),
    m_fragmentSource()
{
}

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) :
    m_vertexID(0),
    m_fragmentID(0),
    m_programID(0),
    m_vertexSource(vertexSource),
    m_fragmentSource(fragmentSource)
{
    const bool success = load();
    assert( success );
}

void
Shader::cleanup()
{
    if(glIsShader(m_vertexID) == GL_TRUE)
    {
        glDeleteShader(m_vertexID);
        m_vertexID = 0;
    }

    if(glIsShader(m_fragmentID) == GL_TRUE)
    {
        glDeleteShader(m_fragmentID);
        m_fragmentID = 0;
    }

    if(glIsProgram(m_programID) == GL_TRUE)
    {
        glDeleteProgram(m_programID);
        m_programID = 0;
    }
}

Shader::~Shader()
{
    cleanup();
}

// Méthodes

std::string
Shader::getGlError(const GLuint& id)
{
    // Récupération de la taille de l'erreur
    GLint tailleErreur(0);
    if (glIsProgram(id)) glGetProgramiv(id, GL_INFO_LOG_LENGTH, &tailleErreur);
    if (glIsShader(id)) glGetShaderiv(id, GL_INFO_LOG_LENGTH, &tailleErreur);
    assert( tailleErreur );

    // Allocation de mémoire
    char *erreur = new char[tailleErreur + 1];

    // Récupération de l'erreur
    glGetShaderInfoLog(id, tailleErreur, &tailleErreur, erreur);
    erreur[tailleErreur] = '\0';

    std::string erreur_string(erreur, tailleErreur);
    delete [] erreur;

    return erreur_string;
}

bool
Shader::load()
{
    cleanup();

    // Compilation des shaders
    if(!compileShader(m_vertexID, GL_VERTEX_SHADER, m_vertexSource)) return false;
    if(!compileShader(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource)) return false;

    // Création du programme
    m_programID = glCreateProgram();

    // Association des shaders
    glAttachShader(m_programID, m_vertexID);
    glAttachShader(m_programID, m_fragmentID);

    // Verrouillage des entrées shader
    glBindAttribLocation(m_programID, 0, "in_Vertex");
    glBindAttribLocation(m_programID, 1, "in_Color");
    glBindAttribLocation(m_programID, 2, "in_TexCoord0");

    // Linkage du programme
    glLinkProgram(m_programID);

    // Vérification du linkage
    GLint erreurLink(0);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &erreurLink);
    if(erreurLink != GL_TRUE)
    {
        std::cout << "Error, can't link program" << std::endl;
        std::cout << getGlError(m_programID) << std::endl;
        return false;
    }

    return true;
}

bool
Shader::compileShader(GLuint &shader, GLenum type, std::string const &fichierSource)
{
    // Création du shader
    shader = glCreateShader(type);


    // Vérification du shader
    if(shader == 0)
    {
        std::cout << "Error, unknown shader type (" << type << ")" << std::endl;
        return false;
    }


    // Flux de lecture
    std::ifstream fichier(fichierSource.c_str());


    // Test d'ouverture
    if(!fichier)
    {
        std::cout << "Error, can't open " << fichierSource << std::endl;
        return false;
    }

    // Lecture
    std::string ligne;
    std::string codeSource;
    while (getline(fichier, ligne))
        codeSource += ligne + '\n';

    // Fermeture du fichier
    fichier.close();

    // Envoi du code source au shader
    const GLchar* chaineCodeSource = codeSource.c_str();
    glShaderSource(shader, 1, &chaineCodeSource, 0);

    // Compilation du shader
    glCompileShader(shader);
    GLint erreurCompilation(0);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);
    if(erreurCompilation != GL_TRUE)
    {
        std::cout << "Error, can't compile shader" << std::endl;
        std::cout << getGlError(shader) << std::endl;
        return false;
    }

    // Sinon c'est que tout s'est bien passé
    return true;
}

// Getter

GLuint Shader::getProgramID() const
{
    return m_programID;
}
