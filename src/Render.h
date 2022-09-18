//
// Created by cboy on 2022/8/26.
//

#ifndef OPENGL_STUDY_RENDER_H
#define OPENGL_STUDY_RENDER_H
#include <glad/glad.h>

#include <iostream>

static const char* items[] = { "emerald", "jade", "obsidian", "pearl", "ruby", "turquoise", "brass",
                               "bronze", "chrome", "copper", "gold" ,"silver", "black plastic", "cyan plastic", "green plastic" ,"red plastic"
        , "white plastic", "yellow plastic" ,"black plastic", "cyan plastic", "green plastic", "green plastic" ,"red plastic"
        , "white plastic" ,"yellow plastic"};

#define ASSERT(x) if(!(x)) __builtin_debugtrap();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char *function,const char *file,int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[opengl error](" << error << ")" << function<<
                  " " << file << ";"<< line << std::endl;

        return false;
    }
    return true;
}

static void Clear()
{
    GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
#define GlCall(_FUNC_) if(_FUNC_) std::cout ""

#endif //OPENGL_STUDY_RENDER_H
