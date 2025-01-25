#pragma once


struct RenderComponent {
	int zIndex;

	RenderComponent(float zIndex) :
		zIndex(zIndex)
	{
	}
};