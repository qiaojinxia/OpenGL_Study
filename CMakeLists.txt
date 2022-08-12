cmake_minimum_required(VERSION 3.19)
project(OpenGL_Study)

set(CMAKE_CXX_STANDARD 14)
if (APPLE)
    set(CMAKE_CXX_FLAGS "-framework Cocoa -framework IOKit -framework OpenGL ")
    # -framework OpenGL -framework CoreVideo
    add_compile_definitions(GL_SILENCE_DEPRECATION)
    add_compile_definitions(GLEW_STATIC)
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
include_directories(src)

set(SOURCE_FILES main.cpp)

link_directories(${PROJECT_SOURCE_DIR}/lib)
add_executable(${PROJECT_NAME}
        src/main.cpp
        includes/glad/src/glad.c)

target_link_libraries(${PROJECT_NAME}
       glfw3  GLEW GLTools )
