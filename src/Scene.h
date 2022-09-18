//
// Created by cboy on 2022/9/9.
//

#ifndef OPENGL_STUDY_SENCE_H
#define OPENGL_STUDY_SENCE_H

#include <vector>
#include "light/Light.h"
#include "SkyBox.h"
#include "Camera.h"
using namespace OpenGl_Light;
namespace OpenGl_3D{
    class Scene {
    public:
        Scene();
        ~Scene();
        void Init();
        void OnUiRender();
        void AddCamera(std::shared_ptr<Camera> camera);
        inline void SetSkybox(std::shared_ptr<SkyBox> skybox){
            skybox = skybox;
        }
        static Scene* GetInstance();
    private:
        std::vector<std::shared_ptr<Camera>> cameras;
        std::shared_ptr<SkyBox> skybox;
        int curCamera;
        std::vector<Light> lights;
        static Scene* m_Sence;
    };
}

#endif //OPENGL_STUDY_SENCE_H
