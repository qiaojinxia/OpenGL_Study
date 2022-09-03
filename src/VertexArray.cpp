//
// Created by cboy on 2022/9/3.
//

#include "VertexArray.h"

namespace OpenGl_3D {
    VertexArray::VertexArray(){
        GLCall(glGenVertexArrays(1, &m_RendererID));
        GLCall(glBindVertexArray(m_RendererID));
    };

    VertexArray::~VertexArray()
    {
        GLCall(glDeleteVertexArrays(1, &m_RendererID));
    }

    void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout){
        Bind(); //vao bind
        vb.Bind(); //vbo bind
        const auto& elements = layout.GetElements();
        unsigned int offset = 0;
        for (unsigned int i = 0; i < elements.size(); i++)
        {
            const auto& element = elements[i];
            //set glad_glVertexAttribPointer;
            GLCall(glVertexAttribPointer(i, element.count, element.type,
                                         element.normalized, layout.GetStride(), (const void*)offset))
            GLCall(glEnableVertexAttribArray(i));
            offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
        }
    }

    void VertexArray::Bind() const{
        GLCall(glBindVertexArray(m_RendererID));
    }
    void VertexArray::Unbind() const{
        GLCall(glBindVertexArray(0));
    };
}