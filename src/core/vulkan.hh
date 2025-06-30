#ifndef VULKAN_CORE_HH
#define VULKAN_CORE_HH

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <spdlog/logger.h>

namespace fxl::render {

    class vulkan {
        VkInstance instance_;
        VkInstanceCreateInfo create_info_;
        VkApplicationInfo app_info_;

    public:
        explicit vulkan(std::string_view const &instance_name);
        ~vulkan();

        static auto check_extensions() -> void;
    };

} // namespace fxl::render

#endif //VULKAN_CORE_HH
