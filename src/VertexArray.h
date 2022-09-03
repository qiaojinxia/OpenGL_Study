//
// Created by cboy on 2022/9/3.
//
#pragma once
#ifndef OPENGL_STUDY_VERTEXARRAY_H
#define OPENGL_STUDY_VERTEXARRAY_H
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace OpenGl_3D {
    class VertexArray
    {
    private:
        unsigned int m_RendererID;
        std::unique_ptr<VertexBuffer>;
        std::unique_ptr<VertexBufferLayout> ;
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

        void Bind() const;
        void Unbind() const;


    };

}
#endif //OPENGL_STUDY_VERTEXARRAY_H
