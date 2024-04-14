#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Calculator/Calculator.h"
//#include "../Calculator/CalculatorPresenter.h"
#include <iostream>
#include <variant>
#include "../Calculator/Function.h"
#include "../Calculator/Variable.h"


TEST_CASE("1")
{

	SECTION("1")
	{
		Calculator calc;

		Variable varX;
		varX.m_name = "x";
		varX.m_value = 4.0;
		Variable varY;
		varY.m_name = "y";
		varY.m_value = 2.0;

		calc.vars.insert(varY);
		calc.vars.insert(varX);
		calc.ids.insert(varY.m_name);
		calc.ids.insert(varX.m_name);

		Function fn;
		fn.SetName("YaddX");
		fn.SetOperator('+');
		fn.SetFirstIdValue(&varX.m_value);
		fn.SetSecondIdValue(&varY.m_value);

		Function fn2;
		fn2.SetName("testFunc");
		fn2.SetOperator('+');
		fn2.SetFirstIdValue(&fn);
		fn2.SetSecondIdValue(&varY.m_value);

		calc.fns.insert(fn);
		calc.ids.insert(fn.GetName());

		calc.fns.insert(fn2);
		calc.ids.insert(fn2.GetName());

		//auto it = calc.fns.find(Function("testFunc"));
		//auto it2 = calc.vars.find(Variable("x"));

		//CHECK(it != calc.fns.end());
		//CHECK(it2 != calc.vars.end());

		//it2->m_value = NAN;
		//it->SetFirstIdValue(&fn);

		auto firstIdValue = fn2.GetFirstIdValue();
		auto secondIdValue = fn2.GetSecondIdValue();
		int check1 = 0;
		int check2 = 0;

		double* p1 = nullptr;
		double* p2 = nullptr;

		if (std::holds_alternative<double*>(firstIdValue))
		{
			double* value = std::get<double*>(firstIdValue);
			check1 = 1;
		}
		else if (std::holds_alternative<Function*>(firstIdValue))
		{
			Function* functionPtr = std::get<Function*>(firstIdValue);
			p1 = std::get<double*>(functionPtr->GetFirstIdValue());
			p2 = std::get<double*>(functionPtr->GetSecondIdValue());
			check1 = 2;
			CHECK(*p1 + *p2 == 6.0);
			varX.m_value = 2.0;
		}
		else
		{
			check1 = -1;
		}

		CHECK(*p1 + *p2 == 4.0);

		/*CHECK(check1 == 2);*/

		if (std::holds_alternative<double*>(secondIdValue))
		{
			double* value = std::get<double*>(secondIdValue);
			check2 = 1;
		}
		else if (std::holds_alternative<Function*>(secondIdValue))
		{
			Function* functionPtr = std::get<Function*>(secondIdValue);
			check2 = 2;
		}
		else
		{
			check2 = -1;
		}

		//CHECK(check2 == 1);
	}
}
