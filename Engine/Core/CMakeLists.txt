#
# Core Module
#

# GLOB pour Public headers
file(GLOB_RECURSE PUBLIC_HEADERS 
    CONFIGURE_DEPENDS
    "Public/*.h"
    "Public/*.hpp"
)

# GLOB pour Private sources
file(GLOB_RECURSE PRIVATE_SOURCES 
    CONFIGURE_DEPENDS
    "Private/*.cpp"
    "Private/*.inl"
)

add_library(Core STATIC)

target_sources(Core 
    PRIVATE ${PUBLIC_HEADERS}
    PRIVATE ${PRIVATE_SOURCES}
)

# Match VS filters to directory structure on disk
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${PUBLIC_HEADERS} ${PRIVATE_SOURCES})

# Link SFML
target_link_libraries(Core 
    PUBLIC 
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        glm
)

# Expose Public/ pour que les includes soient "Core/Application.h"
target_include_directories(Core 
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Public"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Private"
)

# Set as library project in IDE
set_target_properties(Core PROPERTIES FOLDER "Engine/Modules")