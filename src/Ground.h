//
// Created by cboy on 2022/9/9.
//

#ifndef OPENGL_STUDY_GROUND_H
#define OPENGL_STUDY_GROUND_H

#include "utils.h"
#include "vertexbuffer.h"
#include "shader.h"
namespace OpenGl_3D {
    class Ground {
    public:
        void Init();
        void Draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
    public:
        VertexBuffer *mVertexBuffer;
        GLuint mVBO;
        Shader *mShader;
        glm::mat4 mModelMatrix;

    };
}

#endif //OPENGL_STUDY_GROUND_H
