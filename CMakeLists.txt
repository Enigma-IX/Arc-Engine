cmake_minimum_required(VERSION 3.21)

project(GameEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json pour les IDE
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Organisation des projets dans les IDE
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Dependencies
include(Dependencies.cmake)

# Projects
add_subdirectory(Engine)
add_subdirectory(Game)