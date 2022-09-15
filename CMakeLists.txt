cmake_minimum_required(VERSION 3.19)
project(OpenGL_Study)

set(CMAKE_CXX_STANDARD 14)
if (APPLE)
    set(CMAKE_CXX_FLAGS "-framework Cocoa -framework IOKit -framework OpenGL ")
    # -framework OpenGL -framework CoreVideo
    add_compile_definitions(GL_SILENCE_DEPRECATION)
    add_compile_definitions(GLEW_STATIC)
    include_directories(
            /usr/local/include
            /usr/local/lib)
endif ()

include_directories(includes/glad/include)
include_directories(includes/glad/include/glad)
include_directories(includes/glad/include/KHR)
include_directories(includes/glew)
include_directories(includes/glew/include)
include_directories(includes/glew/include/GL)
include_directories(includes/glfw)
include_directories(includes/glfw/include)
include_directories(includes/glfw/include/GLFW)
include_directories(includes/stb)
include_directories(includes)

find_package(assimp)

include_directories(src)
include_directories(
        includes/imgui
        includes/imgui/backends
)

file(GLOB SRC
        includes/imgui/*.h
        includes/imgui/*.cpp
        )

set(SOURCE_FILES assert main.cpp)
set(MAIN_PATH ${PROJECT_SOURCE_DIR})

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Shader.cpp
        src/Shader.h
        src/Texture2D.h
        src/Texture2D.cpp
        src/Camera.h
        src/Camera.cpp

        src/VertexArray.h
        src/VertexArray.cpp
        src/VertexBuffer.h
        src/VertexBuffer.cpp
        src/VertexBufferLayout.h
        src/VertexBufferLayout.cpp

        src/Window.h
        src/Window.cpp

        src/vendor/MaterialReader.cpp
        src/vendor/MaterialReader.h

        src/InputManager.h
        src/InputManager.cpp


        src/State.h
        src/State.cpp


        src/tests/Test.cpp
        src/tests/Test.h

        src/tests/TestClearColor.cpp
        src/tests/TestClearColor.h

        src/tests/TestDrawBox.cpp
        src/tests/TestDrawBox.h


        src/tests/TestLight.cpp
        src/tests/TestLight.h


        src/tests/TestLightMap.cpp
        src/tests/TestLightMap.h

        src/tests/TestLightCaster.cpp
        src/tests/TestLightCaster.h

        src/tests/TestLightMap.cpp
        src/tests/TestLightMap.h

        src/tests/TestLightSpot.h
        src/tests/TestLightSpot.cpp

        src/Mesh.h
        src/Mesh.cpp

        src/tests/TestShaderDissolution.h
        src/tests/TestShaderDissolution.cpp

        src/tests/TestLightSpot.h
        src/tests/TestLightSpot.cpp

        src/tests/TestLoadModel.h
        src/tests/TestLoadModel.cpp

        src/Model.h
        src/Model.cpp

        src/Mesh.h
        src/Mesh.cpp


        src/light/Light.h
        src/light/Light.cpp

        src/light/DirLight.h
        src/light/DirLight.cpp

        src/light/PointLight.h
        src/light/PointLight.cpp


        includes/glad/src/glad.c

        includes/imgui/
        includes/imgui/backends/imgui_impl_opengl3.h
        includes/imgui/backends/imgui_impl_opengl3.cpp
        includes/imgui/backends/imgui_impl_glfw.cpp
        includes/imgui/backends/imgui_impl_glfw.h

        includes/imgui/imgui.h
        includes/imgui/imgui.cpp
        includes/imgui/imgui_draw.cpp
        includes/imgui/imgui_tables.cpp
        includes/imgui/imgui_widgets.cpp
        )

target_link_libraries(${PROJECT_NAME}
       glfw3  GLEW GLTools assimp::assimp)
