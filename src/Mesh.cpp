//
// Created by cboy on 2022/9/14.
//

#include "Mesh.h"
#include <functional>

namespace OpenGl_3D{
    void Mesh::setupMesh()
    {
        m_VAO = std::make_unique<VertexArray>();

        m_VertexBuffer = std::make_unique<VertexBuffer>(&vertices[0],sizeof(vertices));

        m_LayOut = std::make_unique<VertexBufferLayout>();

        m_LayOut->Push<float>(3);//顶点位置
        m_LayOut->Push<float>(3);//顶点法线
        m_LayOut->Push<float>(2);//顶点纹理坐标

        m_VAO->AddBuffer(*m_VertexBuffer,*m_LayOut);

    }


    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        setupMesh();
    }
}