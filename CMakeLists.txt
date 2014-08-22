cmake_minimum_required(VERSION 2.8)

project(app_project)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(deps/glfw)
file(GLOB SRCFILES *.cpp)

include_directories(deps/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/deps/glfw/src)

add_executable(nbody ${SRCFILES})
target_link_libraries(nbody glfw3 GLEW GLU ${GLFW_LIBRARIES})

install(TARGETS nbody DESTINATION bin)

