#pragma once
#include "pch.h"
#include <vulkan/vulkan.h>
#include <vector>
#include "Window.h"
#include "Structs_rename_later.h"

class VulkanContext {
public:
    VulkanContext() = default;
    ~VulkanContext() = default;

    VkInstance& GetInstance()  { return _instance; }
    VkDevice& GetDevice()  { return _device; }
    VkPhysicalDevice& GetPhysicalDevice()  { return _physicalDevice; }
    VkQueue& GetGraphicsQueue()  { return _graphicsQueue; }
    VkQueue& GetPresentQueue()  { return _presentQueue; }
    VkCommandPool& GetCommandPool()  { return _commandPool; }
    VkSurfaceKHR& GetSurface()  { return _surface; }
    
    VkExtent2D& GetSwapChainExtent2D(){ return _swapChainExtent; }
    VkFormat& GetSwapChainFormat(){ return _swapChainImageFormat; }
    std::vector<VkFramebuffer>& GetSwapChainFrameBuffers(){ return _swapChainFramebuffers; }
    std::vector<VkImage>& GetSwapChainImages(){ return _swapChainImages; }
    std::vector<VkImageView>& GetSwapChainImageViews(){ return _swapChainImageViews; }
    VkSwapchainKHR& GetSwapChain(){ return _swapChain; }

    VkRenderPass& GetRenderPass(){ return _renderPass; }





    QueueFamilyIndices& GetQueueFamilyIndices() { return _indices; }


    void CreateSurface( Window* window)
    { window->CreateVulkanSurface(_instance, _surface); }

private:
    VkInstance _instance;
    VkDevice _device;
    VkSurfaceKHR _surface;
    VkPhysicalDevice _physicalDevice;
    VkQueue _graphicsQueue;
    VkQueue _presentQueue;
    VkCommandPool _commandPool;

    VkSwapchainKHR _swapChain;
    std::vector<VkFramebuffer> _swapChainFramebuffers;
    std::vector<VkImage> _swapChainImages;
    std::vector<VkImageView> _swapChainImageViews;
    VkFormat _swapChainImageFormat;
    VkExtent2D _swapChainExtent;


    VkRenderPass _renderPass;




    QueueFamilyIndices _indices;

};