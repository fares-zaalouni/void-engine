#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include "Structs_rename_later.h"
#include "SwapChainManager.h"
#include "VulkanContext.h"

class DeviceManager
{
public:
	~DeviceManager() = default ;
	DeviceManager(VulkanContext& vkContext);
	void CreateInstance();
	bool CheckValidationLayerSupport();
	void PickPhysicalDevice();
	bool IsDeviceSuitable(VkPhysicalDevice device);
	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
	void CreateLogicalDevice();
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

private:
	VulkanContext& _vkContext;

	const std::vector<const char*> _deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
	};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif
};

