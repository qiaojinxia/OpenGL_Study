//
// Created by qiaojinxia on 2022/9/17.
//

#ifndef OPENGL_STUDY_SKYBOX_H
#define OPENGL_STUDY_SKYBOX_H

#include "vector"
#include "TextureCube.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

namespace OpenGl_3D {
    class SkyBox{
    public:
        SkyBox();
        void Draw();
    private:
        std::shared_ptr<TextureCube> m_tBox;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexBufferLayout> m_LayOut;
        std::unique_ptr<VertexArray> m_VAO;
        unsigned int skyboxVAO, skyboxVBO;
    };
}

#endif //OPENGL_STUDY_SKYBOX_H
