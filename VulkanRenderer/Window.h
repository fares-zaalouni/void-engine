#pragma once

#define GLFW_INCLUDE_VULKAN  
#include <GLFW/glfw3.h>
#include <iostream>


class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    void pollEvents();  
    bool shouldClose(); 

    GLFWwindow* getGLFWwindow() { return window; }
    void CreateVulkanSurface(const VkInstance& instance, VkSurfaceKHR& outSurface);

private:
    GLFWwindow* window;
};


