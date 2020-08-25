cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# cmake features
include(ExternalProject)
include(CheckLanguage)

project(RieszFrameLib VERSION 0.1 LANGUAGES CXX
  DESCRIPTION "Frames Library and Executables for Testing"
)

if(NOT MSVC)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)  
endif(NOT MSVC)

# Set a default build type if none was specified
set(default_build_type "RelWithDebInfo") 
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "RelWithDebInfo")
endif()

# Select flags for non multi target systems:
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT MSVC)
  SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
  SET(CMAKE_CXX_FLAGS_RELEASE "-O2")
  SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")
endif()


check_language(CUDA)
if(CMAKE_CUDA_COMPILER)
  enable_language(CUDA)
  message(STATUS "CUDA Compiler Found. Enable CUDA targets")
  option(USE_CUDA "Build CUDA targets" ON)
else()
    message(STATUS "No CUDA Compiler Found. Disable targets.")
endif()

## submodules initializiation
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# pngwrap
#if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/pngwrap/CMakeLists.txt")
#    message(FATAL_ERROR "The submodule PNGWRAP was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
#endif()
#add_subdirectory(extern/pngwrap)
#include_directories(extern/pngwrap/include)

# OpenMP
#find_package(OpenMP REQUIRED)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

# FFTW
#find_path(FFTW_INCLUDES "fftw3.h")
#include_directories(${FFTW_INCLUDES})
#find_library(FFTW_LIB NAMES "fftw3" "fftw3-3" "libfftw3-3" )
#find_library(FFTWF_LIB NAMES "fftw3f" "fftw3f-3" "libfftw3f-3" )
#find_library(FFTWL_LIB NAMES "fftw3l" "fftw3l-3" "libfftw3l-3" )
#set(FFTW_LIBRARIES ${FFTW_LIB} ${FFTWF_LIB} ${FFTWL_LIB})

# Math
if (UNIX) 
  set(MATHLIB "m")
else()
  set(MATHLIB "")
endif()

add_subdirectory(src)
add_subdirectory(app)

#add_executable(DecompositionDouble Decomposition.cpp)
#target_compile_definitions(DecompositionDouble PRIVATE USE_DOUBLE)
#add_executable(DecompositionFloat Decomposition.cpp)
#target_compile_definitions(DecompositionFloat PRIVATE USE_FLOAT)
#add_executable(DecompositionDoubleOMP Decomposition.cpp)
#target_compile_definitions(DecompositionDoubleOMP PRIVATE USE_DOUBLE USE_OMP)

# Test-Framework:
enable_testing()
#add_subdirectory(test)

# Tutorials/Helpers/Testers
#add_subdirectory(tutorial)
#add_subdirectory(cudaTutorial)

# CPack driven installer (future?)
#include (InstallRequiredSystemLibraries)
#set (CPACK_RESOURCE_FILE_LICENSE  
#     "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
#set (CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
#set (CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
#include (CPack)