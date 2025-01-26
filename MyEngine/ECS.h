#pragma once
#include <cstdint>
#include <iostream>
#include "SparseSet.h"
#include <unordered_map>
#include <memory>
#include <typeindex>
#include "Logger.h"
#include <queue>
#include <bitset>

namespace ECS {
	using EntityID = uint32_t;
	constexpr uint16_t NOT_FOUND = static_cast<uint16_t>(-1);
	constexpr std::size_t MAX_COMPONENTS = 64;
	class ECS
	{
	public:
		~ECS() = default;
		ECS(const uint32_t MAX_ENTITIES);
		template<typename Component>
		DataStructure::SparseSet<Component>& GetComponents();
		template<typename T>
		void RegisterComponentSparseSet(const uint32_t MAX_COMPONENT_NUMBER = 1000);
		EntityID CreateEntity();
		void DestroyEntity(const EntityID entityID);
		template<typename Component, typename... Args>
		void AddComponent(const EntityID entityID, Args&&... args);
		template<typename Component>
		void RemoveComponent(const EntityID entityID);
	private:
		template<typename Component>
		uint16_t GetBitSetPosition();

		const uint32_t MAX_ENTITIES;
		uint32_t _currentEntity = 0;
		std::unordered_map<std::type_index, uint16_t> _componentBitMap;
		std::vector<std::unique_ptr<DataStructure::ISparseSet>> _componentSparseSets;
		std::vector<EntityID> _availableEntites;
		DataStructure::SparseSet<std::bitset<MAX_COMPONENTS>> _entitiesBitSets;
		std::vector<bool> _entities;
	};
	
	template<typename Component>
	uint16_t ECS::GetBitSetPosition()
	{
		auto type = std::type_index(typeid(Component));
		auto pos = _componentBitMap.find(type);
		return pos != _componentBitMap.end() ? pos->second : NOT_FOUND;
	}

	template<typename Component, typename ...Args>
	void ECS::AddComponent(const EntityID entityID, Args && ...args)
	{
		uint16_t pos = GetBitSetPosition<Component>();
		LOG_CONSOLE_ASSERT(pos != NOT_FOUND, Log::ERROR, "ECS", "Component sparse set of type \"" + std::string(typeid(Component).name()) + "\" ");
		static_cast<DataStructure::SparseSet<Component>*>(_componentSparseSets[pos].get())->Add(entityID, std::forward<Args>(args)...);
		_entitiesBitSets.Get(entityID)->flip(pos);
	}

	template<typename Component>
	void ECS::RemoveComponent(const EntityID entityID)
	{
		uint16_t pos = GetBitSetPosition<Component>();

		LOG_CONSOLE_ASSERT(pos != NOT_FOUND, Log::ERROR, "REMOVE COMPONENT", "Component type not in use");
		LOG_CONSOLE_ASSERT(_entities[entityID], Log::ERROR, "REMOVE COMPONENT", "Entity not in use");
		LOG_CONSOLE_ASSERT((*_entitiesBitSets.Get(entityID))[pos], Log::ERROR, "REMOVE COMPONENT", "Entity does not have component");

		if (pos != NOT_FOUND && _entities[entityID] && (*_entitiesBitSets.Get(entityID))[pos]) {
			_componentSparseSets[pos].get()->Remove(entityID);
		}
	}

	template<typename Component>
	DataStructure::SparseSet<Component>& ECS::GetComponents()
	{
		auto type = std::type_index(typeid(Component));
		uint16_t pos = GetBitSetPosition<Component>();

		LOG_CONSOLE_ASSERT(pos != NOT_FOUND, Log::ERROR, "Getting Components", "Cant Find Sparse Set for Component Type" + std::string(type.name()));
		return *static_cast<DataStructure::SparseSet<Component>*>(_componentSparseSets[pos].get());
	}
	template<typename T>
	void ECS::RegisterComponentSparseSet(const uint32_t MAX_COMPONENT_NUMBER)
	{
		auto type = std::type_index(typeid(T));
		if (GetBitSetPosition<T>() == NOT_FOUND) {
			_componentBitMap[type] = _componentSparseSets.size();
			_componentSparseSets.emplace_back(std::make_unique<DataStructure::SparseSet<T>>(MAX_ENTITIES, MAX_COMPONENT_NUMBER));
			return;
		}
		
		LOG_CONSOLE(Log::LogType::WARNING, "ECS", "Component's sparse set already initialized for type " + std::string(type.name()));
	}
	
}

