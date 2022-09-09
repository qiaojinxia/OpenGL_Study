//
// Created by cboy on 2022/8/26.
//
#include <glad/glad.h>
#ifndef OPENGL_STUDY_TEXTURE2D_H
#define OPENGL_STUDY_TEXTURE2D_H

namespace OpenGl_3D{
    class Texture2D {
    public:
        Texture2D(const char* texTurePath);
        ~Texture2D();
        void Bind();
        void Bind(int slot);
        void UnBind();
        unsigned int GetID();
    private:
        unsigned int ID;
    };
}



#endif //OPENGL_STUDY_TEXTURE2D_H
