#pragma once
#include <memory>

namespace fxl::render {

    class glfw {
        static bool initialized_;

        explicit glfw();
        ~glfw();
    public:
        [[nodiscard]] static auto initialized() -> bool;
        static auto initialize() -> void;
        static auto terminate() -> void;
    };

}
