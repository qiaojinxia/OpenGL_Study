//
// Created by cboy on 2022/9/3.
//

#ifndef OPENGL_STUDY_TESTCLEARCOLOR_H
#define OPENGL_STUDY_TESTCLEARCOLOR_H

#include "Test.h"
namespace OpenGl_3D{
        class TestClearColor : public Test
        {
        public:
            TestClearColor();
            ~TestClearColor();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;

        private:
            float m_ClearColor[4];
        };

};


#endif //OPENGL_STUDY_TESTCLEARCOLOR_H
