#include <iostream>
#include "Logger.h"
#include "ECS.h"
#include "PositionComponent.h"
#include "PhysicsComponent.h"

int main() {
	ECS::ECS  ecs;
	DataStructure::SparseSet<PositionComponent>& ss = ecs.GetComponents<PositionComponent>();
	DataStructure::SparseSet<PhysicsComponent>& sk = ecs.GetComponents<PhysicsComponent>();
	ss.Add(0, 1, 2, 3);
	sk.Add(1, 5);
	for(int i = 0; i < 99999; i++) 
		ss.Add(i, 1, 2, 3);

	ss.Add(99585, 10, 2, 3);
	std::cout << "X of entity 0: " << ss.Get(99585)->x << std::endl;
	std::cout << "X of entity 1: " <<sk.Get(1)->velocity << std::endl;
	while(true){}
	return 1;
}