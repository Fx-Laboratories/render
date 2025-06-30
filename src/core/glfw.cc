#include "glfw.hh"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace fxl::render {

    bool glfw::initialized_ = false;

    glfw::glfw() = default;
    glfw::~glfw() = default;

    auto glfw::initialize() -> void {
        if (initialized_) {
            spdlog::get("render")->warn("Attempted to doubly-initialize GLFW");
            return;
        }

        if (glfwInit() != GLFW_TRUE) {
            terminate();
            spdlog::get("render")->error("Failed to initialize GLFW");
        }

        initialized_ = true;
        spdlog::get("render")->info("Successfully initialized GLFW");
    }

    auto glfw::terminate() -> void {
        glfwTerminate();
        initialized_ = false;
        spdlog::get("render")->info("Successfully terminated GLFW");
    }

    auto glfw::initialized() -> bool {
        return initialized_;

    }

}