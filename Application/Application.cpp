#include <iostream>
#include "ECS.h"
#include "PositionComponent.h"
#include "Window.h"
#include "InputManager.h"
#include "VulkanRenderer.h"
using namespace EntityComponentSystem;
int main()
{
  
    Window window(1000,800, "hello");
    InputManager inputManager(window.getGLFWwindow());
    VulkanRenderer renderer;
    renderer.Init(&window);
    while (!window.shouldClose()) {
        window.pollEvents();
        renderer.DrawFrame();
    }
    
    
    std::cout << "Hello World!\n";
}

