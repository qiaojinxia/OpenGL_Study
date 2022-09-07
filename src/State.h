//
// Created by cboy on 2022/9/6.
//

#ifndef OPENGL_STUDY_STATE_H
#define OPENGL_STUDY_STATE_H
#include "Camera.h"
#include <vector>
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
    public:
        float lastFrame{0};
        float deltaTime{0};
        std::shared_ptr<Camera> m_Camera;
    private:
        static State* m_State;
        std::vector<char> m_InputStack;
    };
}


#endif //OPENGL_STUDY_STATE_H
