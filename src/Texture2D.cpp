//
// Created by cboy on 2022/8/26.
//

#include "Texture2D.h"
#include "Render.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


namespace OpenGl_3D{
    Texture2D::Texture2D(const char* texTurePath) {

        //创建texture
        GLCall(glGenTextures(1, &ID););
        GLCall(glBindTexture(GL_TEXTURE_2D, ID));

        //为当前绑定的纹理对象设置环绕、过滤方式
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(false);  //需要在stbi_load()之前调用
        unsigned char *data = stbi_load(texTurePath, &width, &height, &nrChannels, 0);
        if (data){
            //加载至缓冲区并生成多级渐远纹理
            GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
            GLCall(glGenerateMipmap(GL_TEXTURE_2D));
        }else{
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    void Texture2D::Bind() {
        GLCall(glActiveTexture(GL_TEXTURE0)); // 在绑定纹理之前先激活纹理单元
        GLCall(glBindTexture(GL_TEXTURE_2D, ID));
    }

    Texture2D::~Texture2D() {

    }

    unsigned int Texture2D::GetID() {
        return ID;
    }

    void Texture2D::UnBind() {
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void Texture2D::Bind(int slot) {
        GLCall(glActiveTexture(GL_TEXTURE0 + slot)); // 在绑定纹理之前先激活纹理单元
        GLCall(glBindTexture(GL_TEXTURE_2D, ID));
    }
}