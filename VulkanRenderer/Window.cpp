#include "pch.h"
#include "Window.h"

Window::Window(int width, int height, const char* title) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::pollEvents() {
    glfwPollEvents();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}


void Window::CreateVulkanSurface(VkInstance instance, VkSurfaceKHR& outSurface) {
    if (glfwCreateWindowSurface(instance, window, nullptr, &outSurface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan surface!");
    }
}

