#
# Dependencies
#
include(FetchContent)

# SFML 3.0.2
find_package(SFML 3.0.2 COMPONENTS graphics window system audio QUIET)
if (NOT SFML_FOUND)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW TRUE
    )
    
    set(SFML_BUILD_AUDIO TRUE CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK FALSE CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS FALSE CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(SFML)
endif()


# GLM
find_package(glm 1.0.1 QUIET)
if (NOT glm_FOUND)
    FetchContent_Declare(
        glm
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.zip
    )
    FetchContent_GetProperties(glm)
    if (NOT glm_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(glm)
        add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
    endif()
endif()
set_target_properties(glm PROPERTIES FOLDER "Dependencies")