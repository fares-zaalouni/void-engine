#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include "Window.h"
struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;
	bool IsComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class VulkanRenderer {
public:
	~VulkanRenderer();
	void Init(Window* window);
	void DrawFrame();


	
private:
	void CreateInstance();
	bool CheckValidationLayerSupport();
	void PickPhysicalDevice();
	bool IsDeviceSuitable(VkPhysicalDevice device);
	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow *window);
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	void CreateSurface(Window* window);
	void CreateLogicalDevice();
	void CreateSwapChain(GLFWwindow* window);
	void CreateImageViews();

	//Shader Module // Refactor later :)
	static std::vector<char> ReadFile(const std::string& filename);
	void CreateGraphicsPipeline();
	VkShaderModule CreateShaderModule(const std::vector<char>& code);
	void CreateRenderPass();
	void CreateFramebuffers();
	void CreateCommandPool();
	void CreateCommandBuffer();
	void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	void CreateSyncObjects();
	
	

	VkInstance _instance;
	VkDevice _device;
	VkPhysicalDevice _physicalDevice;
	VkQueue _graphicsQueue;
	VkQueue _presentQueue;
	VkSurfaceKHR _surface;
	VkSwapchainKHR _swapChain;
	std::vector<VkFramebuffer> _swapChainFramebuffers;
	VkCommandPool _commandPool;
	VkCommandBuffer _commandBuffer;

	VkRenderPass _renderPass;
	VkPipelineLayout _pipelineLayout;
	VkPipeline _graphicsPipeline;

	VkSemaphore _imageAvailableSemaphore;
	VkSemaphore _renderFinishedSemaphore;
	VkFence _inFlightFence;

	std::vector<VkImage> _swapChainImages;
	std::vector<VkImageView> _swapChainImageViews;
	VkFormat _swapChainImageFormat;
	VkExtent2D _swapChainExtent;

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
