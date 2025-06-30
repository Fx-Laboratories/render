#ifndef WINDOW_HH
#define WINDOW_HH

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string_view>


namespace fxl::render {

class window {
    GLFWwindow *instance_;
    public:
    explicit window(int32_t width, int32_t height, std::string_view const& title);

    auto begin_loop() const -> void;

    [[nodiscard]] auto should_close() const noexcept -> bool;

    ~window();

};

}

#endif //WINDOW_HH
