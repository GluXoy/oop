#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Calculator/Calculator.h"
//#include "../Calculator/CalculatorPresenter.h"
#include <iostream>
#include <variant>
#include "../Calculator/Function.h"
#include "../Calculator/Variable.h"


TEST_CASE("Check Calculator Class")
{

	SECTION("Function's firstId point to Variable, should return Variable value")
	{
		Calculator calc;

		Variable varX;
		varX.m_name = "x";
		varX.m_value = 1.0;

		calc.vars.insert(varX);
		calc.ids.insert(varX.m_name);

		Function fnA;
		fnA.SetName("A");
		fnA.SetFirstIdValue(&varX.m_value);
		calc.fns.push_back(fnA);
		calc.ids.insert(fnA.GetName());

		CHECK(calc.Calculate("A") == 1.0);
	}

	SECTION("Function's firstId point to Variable, should return changed Variable value")
	{
		Calculator calc;

		Variable varX;
		varX.m_name = "x";
		varX.m_value = 1.0;

		calc.vars.insert(varX);
		calc.ids.insert(varX.m_name);

		Function fnA;
		fnA.SetName("A");
		fnA.SetFirstIdValue(&varX.m_value);
		calc.fns.push_back(fnA);
		calc.ids.insert(fnA.GetName());

		varX.m_value = 2.0;

		CHECK(calc.Calculate("A") == 2.0);
	}

	SECTION("Function contains 2 arguments pointing to Variable")
	{
		Calculator calc;

		Variable varX;
		varX.m_name = "x";
		varX.m_value = 1.0;

		Variable varY;
		varY.m_name = "y";
		varY.m_value = 2.0;

		calc.vars.insert(varY);
		calc.vars.insert(varX);
		calc.ids.insert(varY.m_name);
		calc.ids.insert(varX.m_name);

		Function fnA;
		fnA.SetName("A");
		fnA.SetFirstIdValue(&varX.m_value);
		fnA.SetSecondIdValue(&varY.m_value);
		calc.fns.push_back(fnA);
		calc.ids.insert(fnA.GetName());

		bool isCorrectFirstId = false;
		if (std::holds_alternative<double*>(fnA.GetFirstIdValue()))
		{
			if (*std::get<double*>(fnA.GetFirstIdValue()) == varX.m_value)
			{
				isCorrectFirstId = true;
			}
		}
		CHECK(isCorrectFirstId == true);

		bool isCorrectSecondId = false;
		if (std::holds_alternative<double*>(fnA.GetSecondIdValue()))
		{
			if (*std::get<double*>(fnA.GetSecondIdValue()) == varY.m_value)
			{
				isCorrectSecondId = true;
			}
		}
		CHECK(isCorrectSecondId == true);

	}

	SECTION("Function contains 2 Variable arguments with operator '+' should return sum")
	{
		Calculator calc;

		Variable varX;
		varX.m_name = "x";
		varX.m_value = 1.0;

		Variable varY;
		varY.m_name = "y";
		varY.m_value = 2.0;

		calc.vars.insert(varY);
		calc.vars.insert(varX);
		calc.ids.insert(varY.m_name);
		calc.ids.insert(varX.m_name);

		Function fnA;
		fnA.SetName("A");
		fnA.SetOperator('+');
		fnA.SetFirstIdValue(&varX.m_value);
		fnA.SetSecondIdValue(&varY.m_value);

		calc.fns.push_back(fnA);
		calc.ids.insert(fnA.GetName());

		CHECK(calc.Calculate("A") == 3.0);
	}

	SECTION("Function contains 2 Variable arguments with operator '-' should return difference")
	{
		Calculator calc;

		Variable varX;
		varX.m_name = "x";
		varX.m_value = 3.0;

		Variable varY;
		varY.m_name = "y";
		varY.m_value = 1.0;

		calc.vars.insert(varY);
		calc.vars.insert(varX);
		calc.ids.insert(varY.m_name);
		calc.ids.insert(varX.m_name);

		Function fnA;
		fnA.SetName("A");
		fnA.SetOperator('-');
		fnA.SetFirstIdValue(&varX.m_value);
		fnA.SetSecondIdValue(&varY.m_value);

		calc.fns.push_back(fnA);
		calc.ids.insert(fnA.GetName());

		CHECK(calc.Calculate("A") == 2.0);
	}

	SECTION("Function contains 2 Variable arguments with operator '*' should return multiplication")
	{
		Calculator calc;

		Variable varX;
		varX.m_name = "x";
		varX.m_value = 3.0;

		Variable varY;
		varY.m_name = "y";
		varY.m_value = 2.0;

		calc.vars.insert(varY);
		calc.vars.insert(varX);
		calc.ids.insert(varY.m_name);
		calc.ids.insert(varX.m_name);

		Function fnA;
		fnA.SetName("A");
		fnA.SetOperator('*');
		fnA.SetFirstIdValue(&varX.m_value);
		fnA.SetSecondIdValue(&varY.m_value);

		calc.fns.push_back(fnA);
		calc.ids.insert(fnA.GetName());

		CHECK(calc.Calculate("A") == 6.0);
	}

	SECTION("Function contains 2 Variable arguments with operator '/' should return division")
	{
		Calculator calc;

		Variable varX;
		varX.m_name = "x";
		varX.m_value = 3.0;

		Variable varY;
		varY.m_name = "y";
		varY.m_value = 2.0;

		calc.vars.insert(varY);
		calc.vars.insert(varX);
		calc.ids.insert(varY.m_name);
		calc.ids.insert(varX.m_name);

		Function fnA;
		fnA.SetName("A");
		fnA.SetOperator('/');
		fnA.SetFirstIdValue(&varX.m_value);
		fnA.SetSecondIdValue(&varY.m_value);

		calc.fns.push_back(fnA);
		calc.ids.insert(fnA.GetName());

		CHECK(calc.Calculate("A") == 1.5);
	}

	SECTION("Function's firstId point to another function with one Variable argument and returned the same result as a referenced function")
	{
		Calculator calc;

		Variable varX;
		varX.m_name = "x";
		varX.m_value = 1.0;

		calc.vars.insert(varX);
		calc.ids.insert(varX.m_name);

		Function fnA;
		fnA.SetName("A");
		fnA.SetFirstIdValue(&varX.m_value);

		Function fnB;
		fnB.SetName("B");
		fnB.SetFirstIdValue(fnA);

		calc.fns.push_back(fnA);
		calc.ids.insert(fnA.GetName());
		calc.fns.push_back(fnB);
		calc.ids.insert(fnB.GetName());

		CHECK(calc.Calculate("B") == 1.0);
	}

	SECTION("Function's firstId point to another function with one Variable argument and returned the same result as a referenced function when Variable was changed")
	{
		Calculator calc;

		Variable varX;
		varX.m_name = "x";
		varX.m_value = 1.0;

		calc.vars.insert(varX);
		calc.ids.insert(varX.m_name);

		Function fnA;
		fnA.SetName("A");
		fnA.SetFirstIdValue(&varX.m_value);

		Function fnB;
		fnB.SetName("B");
		fnB.SetFirstIdValue(fnA);

		calc.fns.push_back(fnA);
		calc.ids.insert(fnA.GetName());
		calc.fns.push_back(fnB);
		calc.ids.insert(fnB.GetName());

		varX.m_value = 2.0;
		CHECK(calc.Calculate("B") == 2.0);
	}

	SECTION("Function's firstId point to another function with 2 Variable arguments and returned the same result as a referenced function")
	{
		Calculator calc;

		Variable varX;
		varX.m_name = "x";
		varX.m_value = 1.0;
		calc.vars.insert(varX);
		calc.ids.insert(varX.m_name);

		Variable varY;
		varY.m_name = "y";
		varY.m_value = 2.0;
		calc.vars.insert(varY);
		calc.ids.insert(varY.m_name);

		Function fnA;
		fnA.SetName("A");
		fnA.SetFirstIdValue(&varX.m_value);
		fnA.SetOperator('+');
		fnA.SetSecondIdValue(&varY.m_value);
		calc.fns.push_back(fnA);
		calc.ids.insert(fnA.GetName());

		Function fnB;
		fnB.SetName("B");
		fnB.SetFirstIdValue(fnA);
		calc.fns.push_back(fnB);
		calc.ids.insert(fnB.GetName());

		CHECK(calc.Calculate("B") == calc.Calculate("A"));
	}

	SECTION("Function contains two Function args that contains pair of Variables for each should return sum of them")
	{
		Calculator calc;

		Variable varX;
		varX.m_name = "x";
		varX.m_value = 1.0;
		calc.vars.insert(varX);
		calc.ids.insert(varX.m_name);

		Variable varY;
		varY.m_name = "y";
		varY.m_value = 2.0;
		calc.vars.insert(varY);
		calc.ids.insert(varY.m_name);

		Variable varI;
		varI.m_name = "i";
		varI.m_value = 3.0;
		calc.vars.insert(varI);
		calc.ids.insert(varI.m_name);

		Variable varJ;
		varJ.m_name = "j";
		varJ.m_value = 4.0;
		calc.vars.insert(varJ);
		calc.ids.insert(varJ.m_name);

		Function fnA;
		fnA.SetName("A");
		fnA.SetOperator('+');
		fnA.SetFirstIdValue(&varX.m_value);
		fnA.SetSecondIdValue(&varY.m_value);
		calc.fns.push_back(fnA);
		calc.ids.insert(fnA.GetName());

		Function fnB;
		fnB.SetName("B");
		fnB.SetOperator('+');
		fnB.SetFirstIdValue(&varI.m_value);
		fnB.SetSecondIdValue(&varJ.m_value);
		calc.fns.push_back(fnB);
		calc.ids.insert(fnB.GetName());

		Function fnC;
		fnC.SetName("C");
		fnC.SetOperator('+');
		fnC.SetFirstIdValue(fnA);
		fnC.SetSecondIdValue(fnB);
		calc.fns.push_back(fnC);
		calc.ids.insert(fnC.GetName());

		CHECK(calc.Calculate("C") == 10.0);
	}

	SECTION("Function contains two Function args that contains pair of Variables for each should return sum of them after one of Variables was changed")
	{
		Calculator calc;

		Variable varX;
		varX.m_name = "x";
		varX.m_value = 1.0;
		calc.vars.insert(varX);
		calc.ids.insert(varX.m_name);

		Variable varY;
		varY.m_name = "y";
		varY.m_value = 2.0;
		calc.vars.insert(varY);
		calc.ids.insert(varY.m_name);

		Variable varI;
		varI.m_name = "i";
		varI.m_value = 3.0;
		calc.vars.insert(varI);
		calc.ids.insert(varI.m_name);

		Variable varJ;
		varJ.m_name = "j";
		varJ.m_value = 4.0;
		calc.vars.insert(varJ);
		calc.ids.insert(varJ.m_name);

		Function fnA;
		fnA.SetName("A");
		fnA.SetOperator('+');
		fnA.SetFirstIdValue(&varX.m_value);
		fnA.SetSecondIdValue(&varY.m_value);
		calc.fns.push_back(fnA);
		calc.ids.insert(fnA.GetName());

		Function fnB;
		fnB.SetName("B");
		fnB.SetOperator('+');
		fnB.SetFirstIdValue(&varI.m_value);
		fnB.SetSecondIdValue(&varJ.m_value);
		calc.fns.push_back(fnB);
		calc.ids.insert(fnB.GetName());

		Function fnC;
		fnC.SetName("C");
		fnC.SetOperator('+');
		fnC.SetFirstIdValue(fnA);
		fnC.SetSecondIdValue(fnB);
		calc.fns.push_back(fnC);
		calc.ids.insert(fnC.GetName());

		varJ.m_value = 5.0;

		CHECK(calc.Calculate("C") == 11.0);
	}
}

TEST_CASE("Million functions test") {
	Calculator calc;
	Variable x0;
	x0.m_name = "x0";
	x0.m_value = 1.0;
	calc.vars.insert(x0);
	calc.ids.insert(x0.m_name);

	Function fn;
	fn.SetName("x1");
	fn.SetOperator('+');
	fn.SetFirstIdValue(&x0.m_value);

	// Создание миллиона функций
	for (int i = 2; i <= 10; ++i)
	{
		Function fn;
		fn.SetName("x" + std::to_string(i));		
		fn.SetOperator('+');
		fn.SetFirstIdValue(calc.fns[i - 2]);
		fn.SetSecondIdValue(&x0.m_value);
		calc.fns.push_back(fn);
		calc.ids.insert(fn.GetName());
	}

	// Вызов Calculate для последней функции
	double result = calc.Calculate("x10");
	CHECK(result == 10.0); // Ожидаемый результат
}
