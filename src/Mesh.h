//
// Created by cboy on 2022/9/14.
//

#ifndef OPENGL_STUDY_MESH_H
#define OPENGL_STUDY_MESH_H
#include "vector"
#include "imgui/imgui.h"
#include "State.h"
#include "string"
#include "Shader.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

#include <assimp/postprocess.h>

namespace OpenGl_3D{
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };
    struct Texture {
        unsigned int id;
        std::string type;
        aiString path;  // 我们储存纹理的路径用于与其它纹理进行比较
    };
    class Mesh {
    public:
        /*  网格数据  */
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        /*  函数  */
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw(Shader shader);
    private:
        /*  渲染数据  */
        /*  渲染数据  */
        unsigned int VAO, VBO, EBO;
        /*  函数  */
        void setupMesh();
    };

};
#endif //OPENGL_STUDY_MESH_H
