//
// Created by cboy on 2022/9/3.
//
#pragma once
#ifndef OPENGL_STUDY_VERTEXBUFFERLAYOUT_H
#define OPENGL_STUDY_VERTEXBUFFERLAYOUT_H
#include <vector>
#include "Render.h"

namespace OpenGl_3D{
    struct VertexBufferElement {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;

        static unsigned int GetSizeOfType(unsigned int type) {
            switch (type) {
                case GL_FLOAT:
                    return 4;
                case GL_UNSIGNED_INT:
                    return 4;
                case GL_UNSIGNED_BYTE:
                    return 1;
            }
            ASSERT(false);
            return 0;
        }
    };

    class VertexBufferLayout
    {
    private:
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride;
    public:
        VertexBufferLayout()
                : m_Stride(0) {}

        template<typename T>
        void Push(unsigned int count);

        inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
        inline unsigned int GetStride() const { return m_Stride; }
    };

};

#endif //OPENGL_STUDY_VERTEXBUFFERLAYOUT_H