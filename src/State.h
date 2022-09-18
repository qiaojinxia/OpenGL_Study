//
// Created by cboy on 2022/9/6.
//

#ifndef OPENGL_STUDY_STATE_H
#define OPENGL_STUDY_STATE_H
#include "Camera.h"
#include <vector>
#include "vendor/MaterialReader.h"
#include "SkyBox.h"
namespace OpenGl_3D{
    class State{
    public:
        State();
        static State* GetInstance();
        std::shared_ptr<Camera> GetCamera();
        void PushInput(char);
        void ReleaseInput(char);
        std::vector<char> GetInput();
        bool CheckInput(char);
        static unsigned int SCR_WIDTH ;
        static unsigned int SCR_HEIGHT ;
        std::shared_ptr<SkyBox> skybox;
    public:
        std::shared_ptr<Reader::MaterialReader> m_Materials;
        float lastFrame{0};
        float deltaTime{0};
        std::shared_ptr<Camera> m_Camera;
        std::shared_ptr<glm::mat4>  m_Proj;
    private:
        static State* m_State;


        std::vector<char> m_InputStack;
    };
}


#endif //OPENGL_STUDY_STATE_H
