cmake_minimum_required(VERSION 3.14)
project(eastl_compare)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (Debug, Release, RelWithDebInfo, MinSizeRel)" FORCE)
endif()

include(FetchContent)

FetchContent_Declare(
    EASTL
    GIT_REPOSITORY https://github.com/electronicarts/EASTL.git
    GIT_TAG        3.21.23
)

# Clang Build Analyzer for compilation time analysis
FetchContent_Declare(
    ClangBuildAnalyzer
    GIT_REPOSITORY https://github.com/aras-p/ClangBuildAnalyzer.git
    GIT_TAG        v1.6.0
)

FetchContent_MakeAvailable(EASTL ClangBuildAnalyzer)

# Options
option(ENABLE_FTIME_TRACE "Enable -ftime-trace for Clang compilation analysis" ON)

# Number of types to instantiate (default 100)
if(NOT DEFINED NUM_TYPES)
    set(NUM_TYPES 100 CACHE STRING "Number of types to instantiate in benchmark" FORCE)
endif()

add_definitions(-DEA_COMPILER_CPP17_ENABLED=1)
add_definitions(-DEASTL_OPENSOURCE=1)
add_definitions(-DNUM_TYPES=${NUM_TYPES})

# Add -ftime-trace flag if enabled and using Clang
if(ENABLE_FTIME_TRACE AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-ftime-trace)
    message(STATUS "Clang Build Analyzer: -ftime-trace enabled")
endif()


add_executable(stl_compilation_benchmark_test benchmark/compilation_benchmark_test.cpp)
target_compile_definitions(stl_compilation_benchmark_test PRIVATE USE_STL=1)

add_executable(eastl_compilation_benchmark_test benchmark/compilation_benchmark_test.cpp eastl_new.cpp)
target_compile_definitions(eastl_compilation_benchmark_test PRIVATE USE_EASTL=1)
target_link_libraries(eastl_compilation_benchmark_test EASTL)