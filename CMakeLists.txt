cmake_minimum_required(VERSION 4.0)
project(zpg)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

if(NOT glm_FOUND)
    find_path(GLM_INCLUDE_DIR glm/glm.hpp HINTS /opt/homebrew/include)
    include_directories(${GLM_INCLUDE_DIR})
endif()

add_executable(OpenGLProject ../zpg_project/main.cpp
        ../zpg_project/Application.cpp
        ../zpg_project/Model.cpp
        ../zpg_project/Scene.cpp
        ../zpg_project/Shader.cpp
        ../zpg_project/ShaderProgram.cpp
        ../zpg_project/DrawableObject.cpp
        ../zpg_project/header/DrawableObject.h
        ../zpg_project/CompositeTransformation.cpp
        ../zpg_project/header/CompositeTransformation.h
        ../zpg_project/header/Transformation.h
        ../zpg_project/header/Scale.h
        ../zpg_project/header/Rotate.h
        ../zpg_project/header/Translate.h
        ../zpg_project/header/Observer.h
        ../zpg_project/Subject.cpp
        ../zpg_project/header/Subject.h
        ../zpg_project/Camera.cpp
        ../zpg_project/header/Camera.h
        InputHandler.cpp
        header/InputHandler.h
        header/ShaderLoader.h
        SceneManager.cpp
        header/SceneManager.h
        scenes/cv5/Forest.cpp
        scenes/cv5/Forest.h
        header/DynamicRotate.h
        scenes/cv5/SphereScene.cpp
        scenes/cv5/SphereScene.h
        Light.cpp
        header/Light.h
        scenes/cv5/TriangleScene.cpp
        scenes/cv5/TriangleScene.h
)

target_link_libraries(OpenGLProject
        glfw
        GLEW::GLEW
        OpenGL::GL
        ${OPENGL_LIBRARIES}
)
