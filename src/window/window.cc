#include "window.hh"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <spdlog/spdlog-inl.h>

namespace fxl::render {
    window::window(const int32_t width, const int32_t height, std::string_view const& title) {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        instance_ = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

        if (!instance_) {
            spdlog::get("render")->error("Failed to create GLFW window {}", title);
        }

        spdlog::get("render")->info("Successfully created GLFW window {}", title);
    }

    auto window::begin_loop() const -> void {
        while (!should_close()) {
            glfwPollEvents();
        }
    }

    [[nodiscard]] auto window::should_close() const noexcept -> bool {
        return glfwWindowShouldClose(instance_);
    }

    window::~window() {
        printf("Destroying GLFW window %s\n", glfwGetWindowTitle(instance_));
        glfwDestroyWindow(instance_);
    }
}