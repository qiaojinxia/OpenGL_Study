//
// Created by qiaojinxia on 2022/9/17.
//

#include "TextureCube.h"
#include <glad/glad.h>
#include "stb_image.h"
#include "iostream"
#include "Render.h"

namespace OpenGl_3D {
    TextureCube::TextureCube(std::vector<std::string> faces) : faces(faces) {
        textureID = loadCubeMap(faces);
    }

    unsigned int TextureCube::loadCubeMap(std::vector<std::string> faces) {
        stbi_set_flip_vertically_on_load(false);  //需要在stbi_load()之前调用
        unsigned int textureID;
        GLCall(glGenTextures(1, &textureID));
        GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, textureID));

        int width, height, nrChannels;
        for (unsigned int i = 0; i < faces.size(); i++)
        {
            unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
                stbi_image_free(data);
            }
        }
        GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));


        return textureID;
    }
}