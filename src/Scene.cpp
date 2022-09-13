//
// Created by cboy on 2022/9/9.
//
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "Scene.h"
namespace OpenGl_3D{
    Scene::Scene(){

    };
    Scene::~Scene(){

    };
    void Scene::Init(){

    };
    void Scene::OnUiRender(){
        ImGui::Begin("Plane");
        const char* items[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon" };
        static int item_current = 1;
        if ImGui::ListBox("listbox", &item_current, items, IM_ARRAYSIZE(items), 10){
            
        }
        ImGui::End();
    };
}