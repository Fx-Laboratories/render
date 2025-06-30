#include "vulkan.hh"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <spdlog/logger.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <vulkan/vulkan.hpp>

#include "../util/version.hh"
#include "glfw.hh"

namespace fxl::render {

     vulkan::vulkan(std::string_view const& instance_name) : instance_(VK_NULL_HANDLE), create_info_(), app_info_() {
         if (!glfw::initialized()) {
             spdlog::get("render")->error("Attempting to initialize vulkan when GLFW has not been initialized");
             throw std::runtime_error("Failed to create Vulkan instance");
         }

        app_info_.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info_.pApplicationName = instance_name.data();
        app_info_.pEngineName = project_name.data();
        app_info_.applicationVersion = VK_MAKE_VERSION(project_major_version, project_minor_version, project_patch_version);
        app_info_.engineVersion = VK_MAKE_VERSION(project_major_version, project_minor_version, project_patch_version);
        app_info_.apiVersion = VK_API_VERSION_1_0;

        create_info_.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info_.pApplicationInfo = &app_info_;

         uint32_t extension_count = 0;
         const char **extensions = glfwGetRequiredInstanceExtensions(&extension_count);
         create_info_.enabledExtensionCount = extension_count;
         create_info_.ppEnabledExtensionNames = extensions;
         create_info_.enabledLayerCount = 0;

         const VkResult result = vkCreateInstance(&create_info_, nullptr, &instance_);

         if (result != VK_SUCCESS) {
             spdlog::get("render")->error("Failed to create Vulkan instance for {}. Vulkan Error Code {}", app_info_.pApplicationName, static_cast<int>(result));
             throw std::runtime_error("Failed to create Vulkan instance");
         }

         spdlog::get("render")->info("Successfully initialized Vulkan instance for {}", app_info_.pApplicationName);
         spdlog::get("render")->info("Vulkan API Version {}", app_info_.apiVersion);
     }

     vulkan::~vulkan() {
         printf("Destroying Vulkan instance...\n");
         vkDestroyInstance(instance_, nullptr);
     }


    auto vulkan::check_extensions() -> void {
         uint32_t extension_count = 0;
         vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

         std::vector<VkExtensionProperties> available_extensions(extension_count);
         vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, available_extensions.data());

         spdlog::get("render")->debug("Found {} extensions", extension_count);

         for (std::size_t i = 0; i < extension_count; ++i) {
             const auto &[extension_name, spec_version] = available_extensions[i];
             spdlog::get("render")->debug("[{}] {}: Version {}", i + 1, extension_name, extension_count);
         }

     }

}