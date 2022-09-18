//
// Created by cboy on 2022/9/14.
//

#include "Mesh.h"
#include <functional>



namespace OpenGl_3D{
    void Mesh::setupMesh()
    {
        GLCall(glGenVertexArrays(1, &VAO))
        GLCall(glGenBuffers(1, &VBO))
        GLCall(glGenBuffers(1, &EBO))

        GLCall(glBindVertexArray(VAO))
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO))

        GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW))

        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO))
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                     &indices[0], GL_STATIC_DRAW))

        // 顶点位置
        GLCall(glEnableVertexAttribArray(0))
        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0))
        // 顶点法线
        GLCall(glEnableVertexAttribArray(1))
        GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal)))
        // 顶点纹理坐标
        GLCall(glEnableVertexAttribArray(2))
        GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords)))

        GLCall(glBindVertexArray(0))
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
            GLCall(glActiveTexture(GL_TEXTURE0 + i)); // 在绑定之前激活相应的纹理单元
            // 获取纹理序号（diffuse_textureN 中的 N）
            std::string number;
            std::string name = textures[i].type;
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++);

            shader.setInt(("material." + name + number).c_str(), i);
            GLCall(glBindTexture(GL_TEXTURE_2D, textures[i].id))
        }
        GLCall(glActiveTexture(GL_TEXTURE0))

        // 绘制网格
        GLCall(glBindVertexArray(VAO))
        GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0))
        GLCall(glBindVertexArray(0))
    }
}