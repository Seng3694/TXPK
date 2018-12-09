#include <catch2/catch.hpp>

#include <TXPK/Core/ServiceLocator.hpp>

template<typename T>
class IMathService
{
public:
	virtual ~IMathService() = default;
	virtual T calculate(const T& lhs, const T& rhs) const = 0;
};

template<typename T>
class AdditionService : public IMathService<T>
{
public:
	inline T calculate(const T& lhs, const T& rhs) const override
	{
		return lhs + rhs;
	}
};

template<typename T>
class SubtractionService : public IMathService<T>
{
public:
	inline T calculate(const T& lhs, const T& rhs) const override
	{
		return lhs - rhs;
	}
};

TEST_CASE("ServiceLocator", "[TXPK/Core/Rectangle]")
{
	using namespace txpk;
	typedef IMathService<int>				  IntMathService;
	typedef AdditionService<int>		      IntAdditionService;
	typedef SubtractionService<int>		      IntSubtractionService;
	typedef std::shared_ptr<IntMathService>   IntMathServicePtr;

	ServiceLocatorPtr locator = ServiceLocator::current();
	locator->clear();

	SECTION("Register an instance")
	{
		IntMathServicePtr mathService = locator->resolve<IntMathService>();
		REQUIRE((mathService == NULL));

		//register addition service as mathservice
		locator->registerInstance<IntMathService>(std::make_shared<IntAdditionService>());
		mathService = locator->resolve<IntMathService>();
		REQUIRE((mathService != NULL));
		//should return same instance => same address
		REQUIRE(&(*mathService) == &(*locator->resolve<IntMathService>()));
		//should be the addition service so test it
		REQUIRE(mathService->calculate(10, 20) == 30);

		locator->registerInstance<IntMathService>(std::make_shared<IntSubtractionService>());
		//registered IMathService<int> should be overriden to a SubtractionService
		REQUIRE(&(*mathService) != &(*locator->resolve<IntMathService>()));
		mathService = locator->resolve<IntMathService>();
		//should be the subtraction service now
		REQUIRE(mathService->calculate(10, 20) == -10);
	}

	SECTION("Register a creator")
	{
		//does not create an instance
		locator->registerCreator<IntMathService>([]() { return std::make_shared<IntAdditionService>(); });
		//when resolve is called a new service should be created
		IntMathServicePtr mathService = locator->resolve<IntMathService>();
		REQUIRE(mathService->calculate(10, 20) == 30);
		//everytime you call resolve, a new instance will be created so check addresses
		REQUIRE(&(*mathService) != &(*locator->resolve<IntMathService>()));
	}

	SECTION("Register an instance of a not pure virtual class")
	{
		locator->registerInstance<IntAdditionService>(std::make_shared<IntAdditionService>());

		REQUIRE((locator->resolve<IntMathService>() == NULL));
		REQUIRE((locator->resolve<IntAdditionService>() != NULL));
	}

	SECTION("Clearing after registration should leave no registrations")
	{
		locator->registerInstance<IntAdditionService>(std::make_shared<IntAdditionService>());
		locator->registerCreator<IntSubtractionService>([]() { return std::make_shared<IntSubtractionService>(); });

		REQUIRE((locator->resolve<IntMathService>() == NULL));
		REQUIRE((locator->resolve<IntAdditionService>() != NULL));
		REQUIRE((locator->resolve<IntSubtractionService>() != NULL));

		locator->clear();

		REQUIRE((locator->resolve<IntMathService>() == NULL));
		REQUIRE((locator->resolve<IntAdditionService>() == NULL));
		REQUIRE((locator->resolve<IntSubtractionService>() == NULL));
	}
}