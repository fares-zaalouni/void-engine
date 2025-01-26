#pragma once
#include "PositionComponent.h"
#include "Component.h"


struct PhysicsComponent {
	float velocity;

	PhysicsComponent(float velocity) :
		velocity(velocity)
	{
	}
};