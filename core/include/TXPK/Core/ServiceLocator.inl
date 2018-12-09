#pragma once

#include "ServiceLocator.hpp"

namespace txpk
{
	template<typename T>
	void ServiceLocator::registerInstance(std::shared_ptr<T> instance)
	{
		uint32 hash = static_cast<uint32>(typeid(T).hash_code());
		auto itr = instances.find(hash);
		if (itr == instances.end())
			instances.emplace(hash, instance);
		else
			instances[itr->first] = instance;

	}

	template<typename T>
	void ServiceLocator::registerCreator(std::function<std::shared_ptr<T>()> creator)
	{
		uint32 hash = static_cast<uint32>(typeid(T).hash_code());
		auto itr = creators.find(hash);
		if (itr == creators.end())
			creators.emplace(hash, creator);
		else
			creators[itr->first] = creator;
	}

	template<typename T>
	std::shared_ptr<T> ServiceLocator::resolve() const
	{
		uint32 hash = static_cast<uint32>(typeid(T).hash_code());
		auto itr1 = instances.find(hash);
		if (itr1 != instances.end())
			return std::static_pointer_cast<T>(itr1->second);

		auto itr2 = creators.find(hash);
		if (itr2 != creators.end())
			return std::static_pointer_cast<T>(itr2->second());

		return nullptr;
	}
}
