#pragma once
#include <vector>
#include <utility>
#include <iostream>
namespace EntityComponentSystem {
	typedef uint32_t EntityID;
}

namespace DataStructure {
	constexpr uint32_t INVALID_INDEX = static_cast<uint32_t>(-1);
	
	class ISparseSet {
	public:
		virtual ~ISparseSet() = default;
		virtual bool Remove(EntityComponentSystem::EntityID entityID) = 0;
	};
	template<typename T>
	class SparseSet: public ISparseSet
	{
	public:
		~SparseSet() {};
		SparseSet(uint32_t MAX_ENTITIES, uint32_t MAX_COMPONENTS);
		template<typename... Args>
		bool Add(EntityComponentSystem::EntityID entityID, Args&&... args);
		bool Remove(EntityComponentSystem::EntityID entityID) override;
		T* Get(EntityComponentSystem::EntityID entityID);
		bool Has(EntityComponentSystem::EntityID entityID);
	private:
		std::vector<uint32_t> _sparse;
		std::vector<T> _dense;
		std::vector<EntityComponentSystem::EntityID> _denseToSparse;
	};
	template<typename T>
	SparseSet<T>::SparseSet(uint32_t MAX_ENTITIES, uint32_t MAX_COMPONENTS): 
		_sparse(MAX_ENTITIES, INVALID_INDEX)
	{
		_dense.reserve(MAX_COMPONENTS);
		_denseToSparse.reserve(MAX_COMPONENTS);
	}
	template<typename T>
	T* SparseSet<T>::Get(EntityComponentSystem::EntityID entityID)
	{
		return (_sparse[entityID] != INVALID_INDEX)  ? &_dense[_sparse[entityID]] : nullptr;
	}

	template<typename T>
	bool SparseSet<T>::Has(EntityComponentSystem::EntityID entityID)
	{
		return _sparse[entityID] != INVALID_INDEX;
	}

	template<typename T>
	template<typename... Args>
	bool SparseSet<T>::Add(EntityComponentSystem::EntityID entityID, Args&&... args)
	{
		if (entityID >= _sparse.size()) return false;
		if (_sparse[entityID] != INVALID_INDEX)
		{
			_dense.emplace(_dense.begin() + _sparse[entityID], std::forward<Args>(args)...);
			return true;
		}
		_sparse[entityID] = _dense.size();
		_denseToSparse.push_back(entityID);
		_dense.emplace_back(std::forward<Args>(args)...);
		return true;
	}
	template<typename T>
	bool SparseSet<T>::Remove(EntityComponentSystem::EntityID entityID)
	{
		if (entityID >= _sparse.size() || _sparse[entityID] == INVALID_INDEX) return false;
	
		uint32_t index = _sparse[entityID];
		if (index != _dense.size() - 1) {
			std::swap(_denseToSparse.back(), _denseToSparse[index]);
			std::swap(_dense.back(), _dense[index]);
			_sparse[_denseToSparse[index]] = index;
		}
		
		_sparse[entityID] = INVALID_INDEX;
		_dense.pop_back();
		_denseToSparse.pop_back();

		return true;
		
	}

	
	

}


