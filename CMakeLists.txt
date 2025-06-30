cmake_minimum_required(VERSION 3.31)
project(fxrender VERSION "0.0.1")

set(CMAKE_CXX_STANDARD 26)

configure_file(src/util/version.hh.in src/util/version.hh)

add_executable(fxrender src/main.cc
        src/window/window.cc
        src/window/window.hh
        src/core/vulkan.cc
        src/core/vulkan.hh
        src/util/version.hh
        src/core/glfw.cc
        src/core/glfw.hh
)

target_link_libraries(fxrender fmt)
target_link_libraries(fxrender spdlog)
target_link_libraries(fxrender glfw)
target_link_libraries(fxrender vulkan)

find_package(Vulkan REQUIRED)
