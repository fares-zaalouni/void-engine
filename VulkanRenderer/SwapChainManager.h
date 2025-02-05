#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "Window.h"
#include "Structs_rename_later.h"
#include "VulkanContext.h"


class SwapChainManager
{
public:
	SwapChainManager(VulkanContext& vkContext);
	static SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface) ;
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);
	void CreateSwapChain(GLFWwindow* window);
	void CreateImageViews();
	void CreateFramebuffers();

private:
	VulkanContext& _vkContext;
};

