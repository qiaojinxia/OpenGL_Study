//
// Created by cboy on 2022/8/11.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp""
#include "glm/gtc/type_ptr.hpp"

//当用户改变窗口的大小的时候，视口也应该被调整。
//我们可以对窗口注册一个回调函数(Callback Function)，
//它会在每次窗口大小被调整的时候被调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// 设置窗口大小
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//C风格字符串 现代OpenGL需要我们至少设置一个顶点和一个片段着色器
//GLSL(OpenGL Shading Language)编写顶点着色器
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec2 aTexCoord;\n"
                                 "out vec2 TexCoord;\n"
                                 "uniform mat4 transform;  //需要cpu传过来这个变换矩阵\n"
                                 "\n"
                                 "void main()\n"
                                 "{\n"
                                 "    gl_Position = transform * vec4(aPos, 1.0f);   //对每个顶点坐标施加变换\n"
                                 "    TexCoord = aTexCoord;\n"
                                 "}";
//GLSL(OpenGL Shading Language)编写片段着色器
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "\n"
                                   "in vec2 TexCoord;\n"
                                   "uniform sampler2D ourTexture;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = texture(ourTexture, TexCoord);\n"
                                   "}";
glm::mat4 trans;         //初始化4维单位矩阵
int main()
{

    // glfw: 初始化和版本配置
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation 创建一个窗口对象 SCR_WIDTH(宽) SCR_HEIGHT(高) "LearnOpenGL"(名称)
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 通知GLFW将我们窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);

    // 我们还需要注册这个函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数：
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);

    //创建顶点shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);


    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);



//顶点数据
    float vertices[] = {
            //     ---- 位置 ----     - 纹理坐标 -
            0.5f,  0.66f, 0.0f,   1.0f, 1.0f,   // 右上
            0.5f, -0.66f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.5f, -0.66f, 0.0f,   0.0f, 0.0f,   // 左下
            -0.5f,  0.66f, 0.0f,   0.0f, 1.0f    // 左上
    };

    //box顶点索引
    unsigned int indices[] = { // 注意索引从0开始!
            0, 1, 3, // 第一个三角形
            1, 2, 3  // 第二个三角形
    };

//创建texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
//为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//加载纹理数据
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);  //需要在stbi_load()之前调用
    unsigned char *data = stbi_load("/Users/cboy/Downloads/OpenGL_Study/src/haha.jpg", &width, &height, &nrChannels, 0);
    if (data){
        //加载至缓冲区并生成多级渐远纹理
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    unsigned int VAO,VBO,EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);


    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glad_glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, sizeof(float) * 5,(void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),(void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        glUseProgram(shaderProgram);
        float timeValue = glfwGetTime();                 //获取时间
//        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;  //利用sin和时间实现颜色值在0-1之间变换
//        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");  //获取shader中的ourColor变量
//        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);  //修改ourColor的值
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        processInput(window);
        //EBo绘制
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


//        glDrawArrays(GL_TRIANGLES, 0, 3);//绘制三角形，第二个参数指定了顶点数组的起始索引，我们这里填0。最后一个参数指定我们打算绘制多少个顶点，三角形3个顶点
        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // 当渲染循环结束后我们需要正确释放/删除之前的分配的所有资源
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        trans = glm::translate(trans, glm::vec3(0.0f, 0.01f, 0.0f));   //创建平移矩阵
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        trans = glm::translate(trans, glm::vec3(0.0f, -0.01f, 0.0f));   //创建平移矩阵
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        trans = glm::translate(trans, glm::vec3(-0.01f, 0.0f, 0.0f));   //创建平移矩阵
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        trans = glm::translate(trans, glm::vec3(0.01f, 0.0f, 0.0f));   //创建平移矩阵
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    }

//    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);  //初始化一个点为(1,0,0,1)
//    glm::mat4 trans;         //初始化4维单位矩阵
//    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));   //创建平移矩阵
//    vec = trans * vec;       //平移矩阵*点
//    glm::mat4 trans;
//    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
//    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}