#pragma once

#include <functional>
#include <memory>
#include <type_traits>
#include <unordered_map>

#include "TXPK/Core/Common.hpp"

namespace txpk
{
	class ServiceLocator;
	typedef std::shared_ptr<ServiceLocator> ServiceLocatorPtr;

	/**
	* \brief The service locator class.
	*/
	class ServiceLocator
	{
	public:
		/**
		* \brief Returns the singleton instance of the ServiceLocator.
		*/
		static const ServiceLocatorPtr current();

		/**
		* \brief Clears all registered creators and instances.
		*/
		void clear();

		/**
		* \brief Registers an instance which can be retrieved with the resolve method.
		* \tparam The interface type.
		* \param instance The instance to register.
		*/
		template<typename T>
		void registerInstance(std::shared_ptr<T> instance);

		/**
		* \brief Registers a creator delegate which creates an instance when resolve is called.
		* \tparam The interface type.
		* \param creator The creation delegate.
		*/
		template<typename T>
		void registerCreator(std::function<std::shared_ptr<T>()> creator);

		/**
		* \brief Resolves the type parameter and looks if an instance or creator is registered with this type.
		* \tparam The interface type.
		* \return Returns the registered instance or creates one with a registered creator. Returns NULL if there is no registration.
		*/
		template<typename T>
		std::shared_ptr<T> resolve() const;

		ServiceLocator& operator=(const ServiceLocator&) = delete;

	private:
		static ServiceLocatorPtr instance; /**< The singleton instance */

		std::unordered_map<uint32, std::shared_ptr<void>> instances; /**< The registered instances */
		std::unordered_map<uint32, std::function<std::shared_ptr<void>()>> creators; /**< The registered creator delegates */

		/**
		* \brief The default constructor.
		*/
		ServiceLocator();
		ServiceLocator(const ServiceLocator&) = delete;
	};
}

#include "TXPK/Core/ServiceLocator.inl"
