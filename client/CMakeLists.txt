project(ndm_client LANGUAGES CXX)

find_package(Boost REQUIRED)
find_package(spdlog REQUIRED)

file(GLOB HEADERS "headers/*.hpp")
file(GLOB SOURCES "sources/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC "headers")
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog Boost::program_options)
