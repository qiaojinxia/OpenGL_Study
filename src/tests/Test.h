//
// Created by cboy on 2022/9/3.
//

#ifndef OPENGL_STUDY_TEST_H
#define OPENGL_STUDY_TEST_H
#include <vector>
#include <functional>
#include <iostream>
#include "Camera.h"

namespace OpenGl_3D{
    class Test {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}
    };

    class TestMenu:public Test{
    public:
        TestMenu(Test*& currentTestPointer);
        void OnImGuiRender() override;
        template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test " << name << std::endl;

			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}

    private:
        Test*& m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;

    };
}


#endif //OPENGL_STUDY_TEST_H
