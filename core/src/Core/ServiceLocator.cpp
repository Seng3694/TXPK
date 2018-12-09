#include "TXPK/Core/ServiceLocator.hpp"

namespace txpk
{
	ServiceLocatorPtr ServiceLocator::instance = NULL;

	ServiceLocator::ServiceLocator()
		: instances(), creators()
	{
	}

	ServiceLocatorPtr const ServiceLocator::current()
	{
		if (instance == NULL)
			instance = std::shared_ptr<ServiceLocator>(new ServiceLocator());
		return instance;
	}

	void ServiceLocator::clear()
	{
		instances.clear();
		creators.clear();
	}
}
