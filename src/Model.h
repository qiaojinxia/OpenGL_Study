//
// Created by cboy on 2022/9/15.
//

#ifndef OPENGL_STUDY_MODEL_H
#define OPENGL_STUDY_MODEL_H

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "Mesh.h"

namespace OpenGl_3D{
    class Model
    {
    public:
        /*  函数   */
        Model(char *path)
        {
            loadModel(path);
        }
        void Draw(Shader shader);
    private:
        /*  模型数据  */
        std::vector<Mesh> meshes;
        std::vector<Texture> textures_loaded;
        std::string directory;
        /*  函数   */
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                                  std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string &directory );
    };
}

#endif //OPENGL_STUDY_MODEL_H
