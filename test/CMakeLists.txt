project(ndm_tests LANGUAGES CXX)

# find_package(Boost REQUIRED)
find_package(spdlog REQUIRED)
find_package(GTest REQUIRED)

# file(GLOB HEADERS "*.hpp")
file(GLOB SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog GTest::gtest GTest::gtest_main)
