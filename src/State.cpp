//
// Created by cboy on 2022/9/6.
//

#include "State.h"
namespace OpenGl_3D{
    unsigned int State::SCR_WIDTH = 1280 ;
    unsigned int State::SCR_HEIGHT = 720 ;
    State* State::m_State = 0;

    State::State(){}

    State* State::GetInstance(){
        if(!m_State)
            m_State = new State();
        return m_State;
    }

    std::shared_ptr<Camera> State::GetCamera(){
        return m_Camera;
    }



    void State::PushInput(char value){
        m_InputStack.push_back(value);
    }

    void State::ReleaseInput(char value){
        for(int i = 0; i < m_InputStack.size(); i++){
            if(m_InputStack[i] == value)
                m_InputStack.erase(m_InputStack.begin() + i);
        }
    }

    std::vector<char> State::GetInput(){
        return m_InputStack;
    }

    bool State::CheckInput(char value){
        for(char c : m_InputStack){
            if(c == value)
                return true;
        }
        return false;
    }




}