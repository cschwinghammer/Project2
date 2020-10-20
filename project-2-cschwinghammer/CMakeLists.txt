# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (Project2)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Detect clang
if(CMAKE_CXX_COMPILER MATCHES ".*clang")
  set(CMAKE_COMPILER_IS_CLANGXX 1)
endif()

add_compile_options(-Wall -Wextra -std=c++11 -g -Werror -x c++)

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
# message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

# if Catch2 is installed globally
find_package(Catch2_FOUND QUIET)
# if Catch2 is not found look for it as a lib dependency
if(NOT Catch2_FOUND)
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/Catch2")
        set (Catch2_FOUND true)
        list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/Catch2/contrib")
        add_subdirectory(lib/Catch2)
    else()
        include(DownloadProject.cmake)
        download_project(PROJ               Catch2
                        GIT_REPOSITORY      https://github.com/catchorg/Catch2.git
                        GIT_TAG             master
                        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )
        if (EXISTS "${Catch2_SOURCE_DIR}")
            set (Catch2_FOUND true)
            list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/contrib")
            add_subdirectory(${Catch2_SOURCE_DIR} ${Catch2_BINARY_DIR})
        else()
            message (FATAL_ERROR "Catch2 not found at expected location ${Catch2_SOURCE_DIR}. \n\tSee the Catch2 docs at https://github.com/catchorg/Catch2/blob/master/docs/cmake-integration.md for details on installing or including it.")
        endif()
    endif()
endif()

add_subdirectory (src)

enable_testing()

# add_test(AllTests ${PROJECT_BINARY_DIR}/bin/Test)
