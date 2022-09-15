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

    void Mesh::Draw(Shader shader) {
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        for(unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // 在绑定之前激活相应的纹理单元
            // 获取纹理序号（diffuse_textureN 中的 N）
            std::string number;
            std::string name = textures[i].type;
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++);

            shader.setInt(("material." + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
        glActiveTexture(GL_TEXTURE0);
        m_VAO->Bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        m_VAO->Unbind();
    }
}