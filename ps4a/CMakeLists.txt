cmake_minimum_required(VERSION 3.16)

project(AniPlayer LANGUAGES CXX)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(AniPlayer
    src/main.cpp
    src/KeyFrame.cpp
    src/Component.cpp
    src/AniPlayer.cpp
)

target_compile_features(AniPlayer PRIVATE cxx_std_17)
target_include_directories(AniPlayer PRIVATE include)
target_link_libraries(AniPlayer PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    nlohmann_json::nlohmann_json
)
