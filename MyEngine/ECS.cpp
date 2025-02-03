#include "ECS.h"
#include "PhysicsComponent.h"
#include "PositionComponent.h"
#include "RenderComponent.h"

using namespace EntityComponentSystem;

ECS::ECS(const uint32_t MAX_ENTITIES): 
	MAX_ENTITIES(MAX_ENTITIES),
	_entitiesBitSets(MAX_ENTITIES, MAX_ENTITIES / 2),
	_entities(MAX_ENTITIES, false)
{
	_availableEntites.reserve(MAX_ENTITIES / 2);
	
}

EntityID ECS::CreateEntity()
{
	EntityID entity;
	if (!_availableEntites.empty()) {
		entity = _availableEntites.back();
		_availableEntites.pop_back();
	}
	else
	{
		LOG_CONSOLE_ASSERT(_currentEntity < MAX_ENTITIES, Log::ERROR, "ADDING ENTITY", "Max entity exceeded");
		entity = _currentEntity++;
		_entitiesBitSets.Add(entity, std::bitset<MAX_COMPONENTS>());
	}
	_entities[entity] = true;
	return entity;
}

void ECS::DestroyEntity(const EntityID entityID)
{
	LOG_CONSOLE_ASSERT(entityID < _currentEntity, Log::ERROR, "DESTROY ENTITY", "Invalid entity ID");
	LOG_CONSOLE_ASSERT(_entities[entityID], Log::ERROR, "DESTROY ENTITY", "Entity not in use");

	// check if entity is in use
	if (entityID < _entities.size() && _entities[entityID])
	{
		std::bitset<MAX_COMPONENTS>* bitset = _entitiesBitSets.Get(entityID);
		for (int i = 0; i < _componentSparseSets.size(); i++)
		{
			if (bitset->test(i))
				_componentSparseSets[i].get()->Remove(entityID);
		}
		_entitiesBitSets.Get(entityID)->reset();
		_entities[entityID] = false;
		_availableEntites.push_back(entityID);
	}
}
