#define FXL_RENDER_ENABLE_DEBUG 1

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "core/glfw.hh"
#include "core/vulkan.hh"
#include "window/window.hh"

auto main() -> int {
    auto render = spdlog::stdout_color_mt("render");
    render->set_level(spdlog::level::debug);
    fxl::render::glfw::initialize();

    fxl::render::vulkan::check_extensions();
    fxl::render::vulkan vk_instance("fxl_test");

    fxl::render::glfw::terminate();

    return 0;
}
