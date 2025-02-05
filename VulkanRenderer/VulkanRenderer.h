#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include "Window.h"
#include "DeviceManager.h"
#include "Structs_rename_later.h"


class VulkanRenderer {
public:
	~VulkanRenderer();
	VulkanRenderer();
	void Init(Window* window);
	void DrawFrame();


	
private:
	
	
	//Shader Module // Refactor later :)
	static std::vector<char> ReadFile(const std::string& filename);
	void CreateGraphicsPipeline();
	VkShaderModule CreateShaderModule(const std::vector<char>& code);
	void CreateRenderPass();
	void CreateCommandPool();
	void CreateCommandBuffer();
	void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	void CreateSyncObjects();
	
	
	VulkanContext _vkContext;
	DeviceManager _deviceManager;
	SwapChainManager _swapChainManager;

	VkCommandPool _commandPool;
	VkCommandBuffer _commandBuffer;

	VkPipelineLayout _pipelineLayout;
	VkPipeline _graphicsPipeline;

	VkSemaphore _imageAvailableSemaphore;
	VkSemaphore _renderFinishedSemaphore;
	VkFence _inFlightFence;

	

	
};
