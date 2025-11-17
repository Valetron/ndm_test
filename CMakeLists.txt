set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/build/conan_toolchain.cmake")
set(QT_CREATOR_SKIP_CONAN_SETUP ON)

cmake_minimum_required(VERSION 3.10)
project(ndm_test LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(ProjectSettings)

add_subdirectory(server)
add_subdirectory(client)
