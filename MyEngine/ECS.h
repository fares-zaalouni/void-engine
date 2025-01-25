#pragma once
#include <cstdint>
#include <iostream>
#include "SparseSet.h"
#include <unordered_map>
#include <memory>
#include <typeindex>
#include "Logger.h"

namespace ECS {
	using EntityID = uint32_t;
	class ECS
	{
	public:
		~ECS() {};
		ECS();
		template<typename T>
		DataStructure::SparseSet<T>& GetComponents();
	private:
		std::unordered_map<std::type_index, std::unique_ptr<DataStructure::ISparseSet>> _componentSparseSets;
		const size_t MAX_ENTITIES = 100000;

		template<typename T>
		void RegisterComponentSparseSet();
	};


	template<typename T>
	DataStructure::SparseSet<T>& ECS::GetComponents()
	{
		auto type = std::type_index(typeid(T));
		auto it = _componentSparseSets.find(type);
		LOG_CONSOLE_ASSERT(it != _componentSparseSets.end(), Log::ERROR, "Getting Components", "Cant Find Sparse Set for Component Type");
		return *dynamic_cast<DataStructure::SparseSet<T>*>(it->second.get());
		
	}
	template<typename T>
	void ECS::RegisterComponentSparseSet()
	{
		auto type = std::type_index(typeid(T));
		if (_componentSparseSets.find(type) == _componentSparseSets.end()) {
			_componentSparseSets[type] = std::make_unique<DataStructure::SparseSet<T>>(MAX_ENTITIES);
		}
		else LOG_CONSOLE(Log::LogType::WARNING, "ECS", "Component's sparse set already initialized!");
	}
}

