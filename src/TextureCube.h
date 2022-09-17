//
// Created by qiaojinxia on 2022/9/17.
//

#ifndef OPENGL_STUDY_TEXTURECUBE_H
#define OPENGL_STUDY_TEXTURECUBE_H

#include <vector>
#include "string"
namespace OpenGl_3D{
    class TextureCube {
    public:
        TextureCube(std::vector<std::string> faces);
    private:
        unsigned int loadCubeMap(std::vector<std::string> faces);
    public:
        unsigned int textureID;
        std::vector<std::string> faces;
    };

}

#endif //OPENGL_STUDY_TEXTURECUBE_H
