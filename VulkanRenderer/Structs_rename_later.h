#pragma once
#include <vulkan/vulkan.h>
#include <optional>

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;
	bool IsComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};