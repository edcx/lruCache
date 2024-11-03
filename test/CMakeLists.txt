cmake_minimum_required(VERSION 3.22)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.7.1
)
FetchContent_MakeAvailable(Catch2)

project(LruCacheTest)

file (GLOB_RECURSE SOURCES source/*.cpp)

# These tests can use the Catch2-provided main
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../include)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

include(Catch)
catch_discover_tests(${PROJECT_NAME})