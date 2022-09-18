//
// Created by cboy on 2022/8/26.
//

#ifndef OPENGL_STUDY_SHADER_H
#define OPENGL_STUDY_SHADER_H

#include <glad/glad.h>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp""
#include "glm/gtc/type_ptr.hpp"
namespace OpenGl_3D{
    class Shader {
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        void use();
        void setBool(const std::string& name,bool value) const;
        void setInt(const std::string& name,int value) const;
        void setFloat(const std::string& name,float value) const;
        void setMat4(const std::string& name,glm::mat4& value) const;
        void setVec3(const std::string& name,float f1,float f2,float f3) const;
        void setVec3(const std::string& name,const glm::vec3& v) const;
        void setVec4(const std::string &name, const glm::vec4 &value) const;
        void setVec4(const std::string &name, float x, float y, float z, float w) const;
        void setMat2(const std::string &name, const glm::mat2 &mat) const;
        void setMat3(const std::string &name, const glm::mat3 &mat) const;
        unsigned int GetRenderID();
    private:
        void  checkCompileErrors(unsigned int shader, std::string type);
    private:
        unsigned int ID;
    };

}


#endif //OPENGL_STUDY_SHADER_H
