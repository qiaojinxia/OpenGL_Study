//
// Created by cboy on 2022/9/9.
//

#ifndef OPENGL_STUDY_SENCE_H
#define OPENGL_STUDY_SENCE_H

#include <vector>
#include "light/Light.h"

using namespace OpenGl_Light;
namespace OpenGl_3D{
    class Scene {
    public:
        Scene();
        ~Scene();
        void Init();
        void OnUiRender();
    private:
        std::vector<Camera> cameras;
        int curCamera;
        std::vector<Light> lights;
    };
}

#endif //OPENGL_STUDY_SENCE_H
