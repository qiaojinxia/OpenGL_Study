//
// Created by cboy on 2022/8/26.
//

#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Render.h"
using namespace std;

namespace OpenGl_3D{
    Shader::Shader(const char* vertexPath, const char* fragmentPath){
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        GLCall(vertex =  glCreateShader(GL_VERTEX_SHADER));
        GLCall(glShaderSource(vertex, 1, &vShaderCode, NULL));
        GLCall(glCompileShader(vertex));
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        GLCall(fragment = glCreateShader(GL_FRAGMENT_SHADER));
        GLCall(glShaderSource(fragment, 1, &fShaderCode, NULL));
        GLCall(glCompileShader(fragment));
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        GLCall(ID = glCreateProgram());
        GLCall(glAttachShader(ID, vertex));
        GLCall(glAttachShader(ID, fragment));
        GLCall(glLinkProgram(ID));
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        GLCall(glDeleteShader(vertex));
        GLCall(glDeleteShader(fragment));
    }
    void Shader::use(){
        GLCall(glUseProgram(ID));
    }
    void Shader::setBool(const std::string& name,bool value) const{
        GLCall(glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value));
    }
    void Shader::setInt(const std::string& name,int value) const{
        GLCall(glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value));
    }

    void Shader::setFloat(const std::string& name,float value) const{
        GLCall(glUniform1f(glGetUniformLocation(ID, name.c_str()), value));
    }
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void Shader::checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
            if (!success)
            {
                GLCall(glGetShaderInfoLog(shader, 1024, NULL, infoLog));
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            GLCall(glGetProgramiv(shader, GL_LINK_STATUS, &success));
            if (!success)
            {
                GLCall(glGetProgramInfoLog(shader, 1024, NULL, infoLog));
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }

    void Shader::setMat4(const string &name, glm::mat4 &value) const {
        GLCall(glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]));
    }

    void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
    {
        GLCall(glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]));
    }
    void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
    {
        GLCall(glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w));
    }

    unsigned int Shader::GetRenderID() {
        return ID;
    }

    void Shader::setVec3(const string &name, float f1, float f2, float f3) const {
        GLCall(glad_glUniform3f(glGetUniformLocation(ID, name.c_str()),f1,f2,f3));
    }

    void Shader::setVec3(const string &name, const glm::vec3 &value) const {
        GLCall(glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]));
    }

    void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        GLCall(glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]));
    }
    // ------------------------------------------------------------------------
    void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        GLCall(glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]));
    }

}