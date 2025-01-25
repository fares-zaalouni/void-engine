#pragma once
#include "PositionComponent.h"


struct PhysicsComponent {
	float velocity;

	PhysicsComponent(float velocity) :
		velocity(velocity)
	{
	}
};