#pragma once
#include <vector>
#include "ECS.h"

namespace DataStructure {
	constexpr size_t INVALID_INDEX = static_cast<size_t>(-1);

	template<typename T>
	class SparseSet
	{
	public:
		SparseSet(uint32_t MAX_ENTITIES);
		template<typename... Args>
		bool add(ECS::EntityID entityID, Args... args);
		bool remove(ECS::EntityID entityID);
		T* get(ECS::EntityID entityID);
	private:
		std::vector<uint32_t> _sparse;
		std::vector<T> _dense;
		std::vector<ECS::EntityID> _denseToSparse;
	};
	template<typename T>
	SparseSet<T>::SparseSet(uint32_t MAX_ENTITIES): 
		_sparse(MAX_ENTITIES, INVALID_INDEX),
		_dense(1000),
		_denseToSparse(1000)
	{
	}
	template<typename T>
	T* SparseSet<T>::get(ECS::EntityID entityID)
	{
		return &_dense(_sparse[entityID]) ? _sparse[entityID] != INVALID_INDEX : nullptr;
	}

	template<typename T>
	template<typename ...Args>
	bool SparseSet<T>::add(ECS::EntityID entityID, Args ...args)
	{
		if (entityID >= _sparse.size()) return false;
		_sparse[entityID] = _dense.size();
		_denseToSparse.push_back(entityID);
		_dense.emplace_back(std::forward<Args>(args));
		return true;
	}
	template<typename T>
	bool SparseSet<T>::remove(ECS::EntityID entityID)
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


