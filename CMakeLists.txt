cmake_minimum_required(VERSION 4.0)
project(Adv_Game_Prog_Tech)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    set(SDL3_PATH "C:/Dev/SDL3")
    set(SDL3_IMAGE_PATH "C:/Dev/sdl3_image")
    include_directories(
            ${SDL3_PATH}/include
            ${SDL3_IMAGE_PATH}/include
    )
    link_directories(
            ${SDL3_PATH}/lib
            ${SDL3_IMAGE_PATH}/lib
            ${PROJECT_SOURCE_DIR}/src
            ${PROJECT_SOURCE_DIR}/src/vendor
            ${PROJECT_SOURCE_DIR}/src/utils
            ${PROJECT_SOURCE_DIR}/src/ecs
            ${PROJECT_SOURCE_DIR}/src/ecs/system
    )
endif ()

add_executable(Adv_Game_Prog_Tech src/main.cpp
        src/Game.cpp
        src/TextureManager.cpp
        src/Map.cpp
        src/GameObject.cpp
        src/utils/Vector.cpp
        src/utils/Collision.cpp
        src/ecs/system/CollisionSystem.cpp
        src/ecs/World.cpp
        src/vendor/tinyxml2.cpp
        src/manager/AssetManager.cpp
        src/ecs/system/AnimationSystem.h
        src/manager/Scene.cpp
)

target_link_libraries(Adv_Game_Prog_Tech
        SDL3
        SDL3_image
)
