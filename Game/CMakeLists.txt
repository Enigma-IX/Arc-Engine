#
# Game Module
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

add_executable(Game)

target_sources(Game 
    PUBLIC ${PUBLIC_HEADERS}
    PRIVATE ${PRIVATE_SOURCES}
)

# Match VS filters to directory structure on disk
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${PUBLIC_HEADERS} ${PRIVATE_SOURCES})

# Link Engine module (qui contient Core et SFML)
target_link_libraries(Game Engine)

# Expose Public/ pour que les includes soient "Game/GameLayer.h"
target_include_directories(Game 
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Public"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Private"
)

# Set working directory for VS debugger
set_target_properties(Game PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Game"
    FOLDER "Game"
)

# Copy SFML DLLs to output directory (Windows uniquement)
if(WIN32)
    add_custom_command(
        TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE:sfml-audio>
            $<TARGET_FILE_DIR:Game>
        COMMENT "Copying SFML DLLs to output directory"
    )
endif()