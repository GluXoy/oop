#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include <iostream>
#include <variant>
#include <string>
#include <fstream>
#include "../Calculator/Calculator.h"
#include "../Calculator/Function.h"
#include "../Calculator/Variable.h"
#include "../Calculator/CalculatorPresenter.h"


TEST_CASE("Check Calculator Class")
{

	SECTION("Function's firstId point to Variable, should return Variable value")
	{
		Calculator calc;

		Variable varX;
		varX.SetName("x");
		varX.SetValue(1.0);

		calc.AddVariable(varX);

		Function fnA;
		fnA.SetName("A");
		fnA.SetFirstIdValue(varX);
		calc.AddFunction(fnA);

		CHECK(calc.Calculate("A") == 1.0);
	}

	SECTION("Function's firstId point to Variable, should return changed Variable value")
	{
		Calculator calc;

		Variable varX;
		varX.SetName("x");
		varX.SetValue(1.0);
		calc.AddVariable(varX);

		Function fnA;
		fnA.SetName("A");
		fnA.SetFirstIdValue(*calc.GetVariable("x"));
		calc.AddFunction(fnA);

		calc.ChangeVariable("x", 2.0);

		CHECK(calc.Calculate("A") == 2.0);
	}

	SECTION("Function contains 2 arguments pointing to Variable")
	{
		Calculator calc;

		Variable varX;
		varX.SetName("x");
		varX.SetValue(1.0);
		calc.AddVariable(varX);

		Variable varY;
		varY.SetName("y");
		varY.SetValue(2.0);
		calc.AddVariable(varY);


		Function fnA;
		fnA.SetName("A");
		fnA.SetFirstIdValue(varX);
		fnA.SetSecondIdValue(varY);
		calc.AddFunction(fnA);

		bool isCorrectFirstId = false;
		if (std::holds_alternative<const Variable*>(fnA.GetFirstIdValue()))
		{
			if (std::get<const Variable*>(fnA.GetFirstIdValue())->GetValue() == varX.GetValue())
			{
				isCorrectFirstId = true;
			}
		}
		CHECK(isCorrectFirstId == true);

		bool isCorrectSecondId = false;
		if (std::holds_alternative<const Variable*>(fnA.GetSecondIdValue()))
		{
			if (std::get<const Variable*>(fnA.GetSecondIdValue())->GetValue() == varY.GetValue())
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
		varX.SetName("x");
		varX.SetValue(1.0);
		calc.AddVariable(varX);

		Variable varY;
		varY.SetName("y");
		varY.SetValue(2.0);
		calc.AddVariable(varY);

		Function fnA;
		fnA.SetName("A");
		fnA.SetOperator('+');
		fnA.SetFirstIdValue(varX);
		fnA.SetSecondIdValue(varY);
		calc.AddFunction(fnA);

		CHECK(calc.Calculate("A") == 3.0);
	}

	SECTION("Function contains 2 Variable arguments with operator '-' should return difference")
	{
		Calculator calc;

		Variable varX;
		varX.SetName("x");
		varX.SetValue(3.0);
		calc.AddVariable(varX);

		Variable varY;
		varY.SetName("y");
		varY.SetValue(1.0);
		calc.AddVariable(varY);

		Function fnA;
		fnA.SetName("A");
		fnA.SetOperator('-');
		fnA.SetFirstIdValue(varX);
		fnA.SetSecondIdValue(varY);
		calc.AddFunction(fnA);

		CHECK(calc.Calculate("A") == 2.0);
	}

	SECTION("Function contains 2 Variable arguments with operator '*' should return multiplication")
	{
		Calculator calc;

		Variable varX;
		varX.SetName("x");
		varX.SetValue(3.0);
		calc.AddVariable(varX);

		Variable varY;
		varY.SetName("y");
		varY.SetValue(2.0);
		calc.AddVariable(varY);

		Function fnA;
		fnA.SetName("A");
		fnA.SetOperator('*');
		fnA.SetFirstIdValue(varX);
		fnA.SetSecondIdValue(varY);
		calc.AddFunction(fnA);

		CHECK(calc.Calculate("A") == 6.0);
	}

	SECTION("Function contains 2 Variable arguments with operator '/' should return division")
	{
		Calculator calc;

		Variable varX;
		varX.SetName("x");
		varX.SetValue(3.0);
		calc.AddVariable(varX);

		Variable varY;
		varY.SetName("y");
		varY.SetValue(2.0);
		calc.AddVariable(varY);

		Function fnA;
		fnA.SetName("A");
		fnA.SetOperator('/');
		fnA.SetFirstIdValue(varX);
		fnA.SetSecondIdValue(varY);
		calc.AddFunction(fnA);

		CHECK(calc.Calculate("A") == 1.5);
	}

	SECTION("Function's firstId point to another function with one Variable argument and returned the same result as a referenced function")
	{
		Calculator calc;

		Variable varX;
		varX.SetName("x");
		varX.SetValue(1.0);
		calc.AddVariable(varX);

		Function fnA;
		fnA.SetName("A");
		fnA.SetFirstIdValue(varX);
		calc.AddFunction(fnA);

		Function fnB;
		fnB.SetName("B");
		fnB.SetFirstIdValue(fnA);
		calc.AddFunction(fnB);

		CHECK(calc.Calculate("B") == 1.0);
	}

	SECTION("Function's firstId point to another function with one Variable argument and returned the same result as a referenced function when Variable was changed")
	{
		Calculator calc;

		Variable varX;
		varX.SetName("x");
		varX.SetValue(1.0);
		calc.AddVariable(varX);

		Function fnA;
		fnA.SetName("A");
		fnA.SetFirstIdValue(*calc.GetVariable("x"));
		calc.AddFunction(fnA);

		Function fnB;
		fnB.SetName("B");
		fnB.SetFirstIdValue(*calc.GetFunction("A"));
		calc.AddFunction(fnB);

		calc.ChangeVariable("x", 2.0);

		CHECK(calc.Calculate("B") == 2.0);
	}

	SECTION("Function's firstId point to another function with 2 Variable arguments and returned the same result as a referenced function")
	{
		Calculator calc;

		Variable varX;
		varX.SetName("x");
		varX.SetValue(1.0);
		calc.AddVariable(varX);

		Variable varY;
		varY.SetName("y");
		varY.SetValue(2.0);
		calc.AddVariable(varY);

		Function fnA;
		fnA.SetName("A");
		fnA.SetFirstIdValue(*calc.GetVariable("x"));
		fnA.SetOperator('+');
		fnA.SetSecondIdValue(*calc.GetVariable("y"));
		calc.AddFunction(fnA);

		Function fnB;
		fnB.SetName("B");
		fnB.SetFirstIdValue(*calc.GetFunction("A"));
		calc.AddFunction(fnB);

		CHECK(calc.Calculate("B") == calc.Calculate("A"));
	}

	SECTION("Function contains two Function args that contains pair of Variables for each should return sum of them")
	{
		Calculator calc;

		Variable varX;
		varX.SetName("x");
		varX.SetValue(1.0);
		calc.AddVariable(varX);

		Variable varY;
		varY.SetName("y");
		varY.SetValue(2.0);
		calc.AddVariable(varY);

		Variable varI;
		varI.SetName("i");
		varI.SetValue(3.0);
		calc.AddVariable(varI);

		Variable varJ;
		varJ.SetName("j");
		varJ.SetValue(4.0);
		calc.AddVariable(varJ);

		Function fnA;
		fnA.SetName("A");
		fnA.SetOperator('+');
		fnA.SetFirstIdValue(*calc.GetVariable("x"));
		fnA.SetSecondIdValue(*calc.GetVariable("y"));
		calc.AddFunction(fnA);

		Function fnB;
		fnB.SetName("B");
		fnB.SetOperator('+');
		fnB.SetFirstIdValue(*calc.GetVariable("i"));
		fnB.SetSecondIdValue(*calc.GetVariable("j"));
		calc.AddFunction(fnB);

		Function fnC;
		fnC.SetName("C");
		fnC.SetOperator('+');
		fnC.SetFirstIdValue(*calc.GetFunction("A"));
		fnC.SetSecondIdValue(*calc.GetFunction("B"));
		calc.AddFunction(fnC);

		CHECK(calc.Calculate("C") == 10.0);
	}

	SECTION("Function contains two Function args that contains pair of Variables for each should return sum of them after one of Variables was changed")
	{
		Calculator calc;

		Variable varX;
		varX.SetName("x");
		varX.SetValue(1.0);
		calc.AddVariable(varX);

		Variable varY;
		varY.SetName("y");
		varY.SetValue(2.0);
		calc.AddVariable(varY);

		Variable varI;
		varI.SetName("i");
		varI.SetValue(3.0);
		calc.AddVariable(varI);

		Variable varJ;
		varJ.SetName("j");
		varJ.SetValue(4.0);
		calc.AddVariable(varJ);

		Function fnA;
		fnA.SetName("A");
		fnA.SetOperator('+');
		fnA.SetFirstIdValue(*calc.GetVariable("x"));
		fnA.SetSecondIdValue(*calc.GetVariable("y"));
		calc.AddFunction(fnA);

		Function fnB;
		fnB.SetName("B");
		fnB.SetOperator('+');
		fnB.SetFirstIdValue(*calc.GetVariable("i"));
		fnB.SetSecondIdValue(*calc.GetVariable("j"));
		calc.AddFunction(fnB);

		Function fnC;
		fnC.SetName("C");
		fnC.SetOperator('+');
		fnC.SetFirstIdValue(*calc.GetFunction("A"));
		fnC.SetSecondIdValue(*calc.GetFunction("B"));
		calc.AddFunction(fnC);

		calc.ChangeVariable("j", 5.0);

		CHECK(calc.Calculate("C") == 11.0);
	}

	SECTION("Fibbonachi testing")
	{
		Calculator calc;

		Variable v0;
		v0.SetName("v0");
		v0.SetValue(0.0);
		calc.AddVariable(v0);

		Variable v1;
		v1.SetName("v1");
		v1.SetValue(1.0);
		calc.AddVariable(v1);

		Function fb0;
		fb0.SetName("fb0");
		fb0.SetFirstIdValue(*calc.GetVariable("v0"));
		calc.AddFunction(fb0);

		Function fb1;
		fb1.SetName("fb1");
		fb1.SetFirstIdValue(*calc.GetVariable("v1"));
		calc.AddFunction(fb1);

		Function fb2;
		fb2.SetName("fb2");
		fb2.SetOperator('+');
		fb2.SetFirstIdValue(*calc.GetFunction("fb0"));
		fb2.SetSecondIdValue(*calc.GetFunction("fb1"));
		calc.AddFunction(fb2);

		CHECK(calc.Calculate(fb2.GetName()) == 1.0);

		Function fb3;
		fb3.SetName("fb3");
		fb3.SetOperator('+');
		fb3.SetFirstIdValue(*calc.GetFunction("fb1"));
		fb3.SetSecondIdValue(*calc.GetFunction("fb2"));
		calc.AddFunction(fb3);

		CHECK(calc.Calculate(fb3.GetName()) == 2.0);
	}
}

TEST_CASE("Check CalculatorPresenter Class")
{
	SECTION("Fibonacci testing")
	{
		Calculator calc;

		Variable v0;
		v0.SetName("v0");
		v0.SetValue(0.0);
		calc.AddVariable(v0);

		Variable v1;
		v1.SetName("v1");
		v1.SetValue(1.0);
		calc.AddVariable(v1);

		Function fb0;
		fb0.SetName("fb0");
		fb0.SetFirstIdValue(*calc.GetVariable("v0"));
		calc.AddFunction(fb0);

		Function fb1;
		fb1.SetName("fb1");
		fb1.SetFirstIdValue(*calc.GetVariable("v1"));
		calc.AddFunction(fb1);

		for (int i = 2; i <= 100; ++i)
		{
			Function fn;
			std::string fnName = "fb" + std::to_string(i);
			fn.SetName(fnName);
			fn.SetOperator('+');
			fn.SetFirstIdValue(*calc.GetFunction("fb" + std::to_string(i - 1)));
			fn.SetSecondIdValue(*calc.GetFunction("fb" + std::to_string(i - 2)));
			calc.AddFunction(fn);
			//CHECK(calc.Calculate("fb" + std::to_string(i)) == 2.0);
		}
		
		CHECK(calc.Calculate("fb50") == 7.0);
		calc.ChangeVariable("v0", 1.0);
		CHECK(calc.Calculate("fb50") == 7.0);
	}
}

