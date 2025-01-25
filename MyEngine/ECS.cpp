#include "ECS.h"
#include "PhysicsComponent.h"
#include "PositionComponent.h"
#include "RenderComponent.h"


ECS::ECS::ECS()
{
	//Initializing component's sparse sets
	RegisterComponentSparseSet<PositionComponent>();
	RegisterComponentSparseSet<PhysicsComponent>();
	RegisterComponentSparseSet<RenderComponent>();
	//RegisterComponentSparseSet<PositionComponent>();

}
