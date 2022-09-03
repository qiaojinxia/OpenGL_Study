//
// Created by cboy on 2022/9/3.
//
#pragma once
#ifndef OPENGL_STUDY_VERTEXBUFFER_H
#define OPENGL_STUDY_VERTEXBUFFER_H

namespace OpenGl_3D{
    class VertexBuffer
    {
    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;
    private:
        unsigned int m_RendererID;
    };


}

#endif //OPENGL_STUDY_VERTEXBUFFER_H
