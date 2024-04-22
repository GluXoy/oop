﻿#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include <iostream>
#include <variant>
#include <string>
#include <fstream>
#include "../Calculator/Calculator.h"
#include "../Calculator/Function.h"
#include "../Calculator/Variable.h"
#include "../Calculator/CalculatorPresenter.h"


//TEST_CASE("Check Calculator Class")
//{

	//SECTION("Function's firstId point to Variable, should return Variable value")
	//{
	//	Calculator calc;

	//	Variable varX;
	//	varX.SetName("x");
	//	varX.SetValue(1.0);

	//	calc.vars.emplace(varX.GetName(), varX);
	//	calc.ids.insert(varX.GetName());

	//	Function fnA;
	//	fnA.SetName("A");
	//	fnA.SetFirstIdValue(varX);
	//	calc.fns.push_back(fnA);
	//	calc.ids.insert(fnA.GetName());

	//	CHECK(calc.Calculate("A") == 1.0);
	//}

	//SECTION("Function's firstId point to Variable, should return changed Variable value")
	//{
	//	Calculator calc;

	//	Variable varX;
	//	varX.SetName("x");
	//	varX.SetValue(1.0);

	//	calc.vars.emplace(varX.GetName(), varX);
	//	calc.ids.insert(varX.GetName());

	//	Function fnA;
	//	fnA.SetName("A");
	//	fnA.SetFirstIdValue(varX);
	//	calc.fns.push_back(fnA);
	//	calc.ids.insert(fnA.GetName());

	//	varX.SetValue(2.0);

	//	CHECK(calc.Calculate("A") == 2.0);
	//}

	//SECTION("Function contains 2 arguments pointing to Variable")
	//{
	//	Calculator calc;

	//	Variable varX;
	//	varX.SetName("x");
	//	varX.SetValue(1.0);

	//	calc.vars.emplace(varX.GetName(), varX);
	//	calc.ids.insert(varX.GetName());

	//	Variable varY;
	//	varY.SetName("y");
	//	varY.SetValue(2.0);

	//	calc.vars.emplace(varY.GetName(), varY);
	//	calc.ids.insert(varY.GetName());


	//	Function fnA;
	//	fnA.SetName("A");
	//	fnA.SetFirstIdValue(varX);
	//	fnA.SetSecondIdValue(varY);
	//	calc.fns.push_back(fnA);
	//	calc.ids.insert(fnA.GetName());

	//	bool isCorrectFirstId = false;
	//	if (std::holds_alternative<Variable*>(fnA.GetFirstIdValue()))
	//	{
	//		if (std::get<Variable*>(fnA.GetFirstIdValue())->GetValue() == varX.GetValue())
	//		{
	//			isCorrectFirstId = true;
	//		}
	//	}
	//	CHECK(isCorrectFirstId == true);

	//	bool isCorrectSecondId = false;
	//	if (std::holds_alternative<Variable*>(fnA.GetSecondIdValue()))
	//	{
	//		if (std::get<Variable*>(fnA.GetSecondIdValue())->GetValue() == varY.GetValue())
	//		{
	//			isCorrectSecondId = true;
	//		}
	//	}
	//	CHECK(isCorrectSecondId == true);

	//}

	//SECTION("Function contains 2 Variable arguments with operator '+' should return sum")
	//{
	//	Calculator calc;

	//	Variable varX;
	//	varX.SetName("x");
	//	varX.SetValue(1.0);
	//	calc.vars.emplace(varX.GetName(), varX);
	//	calc.ids.insert(varX.GetName());

	//	Variable varY;
	//	varY.SetName("y");
	//	varY.SetValue(2.0);
	//	calc.vars.emplace(varY.GetName(), varY);
	//	calc.ids.insert(varY.GetName());

	//	Function fnA;
	//	fnA.SetName("A");
	//	fnA.SetOperator('+');
	//	fnA.SetFirstIdValue(varX);
	//	fnA.SetSecondIdValue(varY);

	//	calc.fns.push_back(fnA);
	//	calc.ids.insert(fnA.GetName());

	//	CHECK(calc.Calculate("A") == 3.0);
	//}

	//SECTION("Function contains 2 Variable arguments with operator '-' should return difference")
	//{
	//	Calculator calc;

	//	Variable varX;
	//	varX.SetName("x");
	//	varX.SetValue(3.0);
	//	calc.vars.emplace(varX.GetName(), varX);
	//	calc.ids.insert(varX.GetName());

	//	Variable varY;
	//	varY.SetName("y");
	//	varY.SetValue(1.0);
	//	calc.vars.emplace(varY.GetName(), varY);
	//	calc.ids.insert(varY.GetName());

	//	Function fnA;
	//	fnA.SetName("A");
	//	fnA.SetOperator('-');
	//	fnA.SetFirstIdValue(varX);
	//	fnA.SetSecondIdValue(varY);

	//	calc.fns.push_back(fnA);
	//	calc.ids.insert(fnA.GetName());

	//	CHECK(calc.Calculate("A") == 2.0);
	//}

	//SECTION("Function contains 2 Variable arguments with operator '*' should return multiplication")
	//{
	//	Calculator calc;

	//	Variable varX;
	//	varX.SetName("x");
	//	varX.SetValue(3.0);
	//	calc.vars.emplace(varX.GetName(), varX);
	//	calc.ids.insert(varX.GetName());

	//	Variable varY;
	//	varY.SetName("y");
	//	varY.SetValue(2.0);
	//	calc.vars.emplace(varY.GetName(), varY);
	//	calc.ids.insert(varY.GetName());

	//	Function fnA;
	//	fnA.SetName("A");
	//	fnA.SetOperator('*');
	//	fnA.SetFirstIdValue(varX);
	//	fnA.SetSecondIdValue(varY);

	//	calc.fns.push_back(fnA);
	//	calc.ids.insert(fnA.GetName());

	//	CHECK(calc.Calculate("A") == 6.0);
	//}

	//SECTION("Function contains 2 Variable arguments with operator '/' should return division")
	//{
	//	Calculator calc;

	//	Variable varX;
	//	varX.SetName("x");
	//	varX.SetValue(3.0);
	//	calc.vars.emplace(varX.GetName(), varX);
	//	calc.ids.insert(varX.GetName());

	//	Variable varY;
	//	varY.SetName("y");
	//	varY.SetValue(2.0);
	//	calc.vars.emplace(varY.GetName(), varY);
	//	calc.ids.insert(varY.GetName());

	//	Function fnA;
	//	fnA.SetName("A");
	//	fnA.SetOperator('/');
	//	fnA.SetFirstIdValue(varX);
	//	fnA.SetSecondIdValue(varY);

	//	calc.fns.push_back(fnA);
	//	calc.ids.insert(fnA.GetName());

	//	CHECK(calc.Calculate("A") == 1.5);
	//}

	//SECTION("Function's firstId point to another function with one Variable argument and returned the same result as a referenced function")
	//{
	//	Calculator calc;

	//	Variable varX;
	//	varX.SetName("x");
	//	varX.SetValue(1.0);
	//	calc.vars.emplace(varX.GetName(), varX);
	//	calc.ids.insert(varX.GetName());

	//	Function fnA;
	//	fnA.SetName("A");
	//	fnA.SetFirstIdValue(varX);

	//	Function fnB;
	//	fnB.SetName("B");
	//	fnB.SetFirstIdValue(fnA);

	//	calc.fns.push_back(fnA);
	//	calc.ids.insert(fnA.GetName());
	//	calc.fns.push_back(fnB);
	//	calc.ids.insert(fnB.GetName());

	//	CHECK(calc.Calculate("B") == 1.0);
	//}

	//SECTION("Function's firstId point to another function with one Variable argument and returned the same result as a referenced function when Variable was changed")
	//{
	//	Calculator calc;

	//	Variable varX;
	//	varX.SetName("x");
	//	varX.SetValue(1.0);
	//	calc.vars.emplace(varX.GetName(), varX);
	//	calc.ids.insert(varX.GetName());

	//	Function fnA;
	//	fnA.SetName("A");
	//	fnA.SetFirstIdValue(varX);

	//	Function fnB;
	//	fnB.SetName("B");
	//	fnB.SetFirstIdValue(fnA);

	//	calc.fns.push_back(fnA);
	//	calc.ids.insert(fnA.GetName());
	//	calc.fns.push_back(fnB);
	//	calc.ids.insert(fnB.GetName());

	//	varX.SetValue(2.0);
	//	CHECK(calc.Calculate("B") == 2.0);
	//}

	//SECTION("Function's firstId point to another function with 2 Variable arguments and returned the same result as a referenced function")
	//{
	//	Calculator calc;

	//	Variable varX;
	//	varX.SetName("x");
	//	varX.SetValue(1.0);
	//	calc.vars.emplace(varX.GetName(), varX);
	//	calc.ids.insert(varX.GetName());

	//	Variable varY;
	//	varY.SetName("y");
	//	varY.SetValue(2.0);
	//	calc.vars.emplace(varY.GetName(), varY);
	//	calc.ids.insert(varY.GetName());

	//	Function fnA;
	//	fnA.SetName("A");
	//	fnA.SetFirstIdValue(varX);
	//	fnA.SetOperator('+');
	//	fnA.SetSecondIdValue(varY);
	//	calc.fns.push_back(fnA);
	//	calc.ids.insert(fnA.GetName());

	//	Function fnB;
	//	fnB.SetName("B");
	//	fnB.SetFirstIdValue(fnA);
	//	calc.fns.push_back(fnB);
	//	calc.ids.insert(fnB.GetName());

	//	CHECK(calc.Calculate("B") == calc.Calculate("A"));
	//}

	//SECTION("Function contains two Function args that contains pair of Variables for each should return sum of them")
	//{
	//	Calculator calc;

	//	Variable varX;
	//	varX.SetName("x");
	//	varX.SetValue(1.0);
	//	calc.vars.emplace(varX.GetName(), varX);
	//	calc.ids.insert(varX.GetName());

	//	Variable varY;
	//	varY.SetName("y");
	//	varY.SetValue(2.0);
	//	calc.vars.emplace(varY.GetName(), varY);
	//	calc.ids.insert(varY.GetName());

	//	Variable varI;
	//	varI.SetName("i");
	//	varI.SetValue(3.0);
	//	calc.vars.emplace(varI.GetName(), varI);
	//	calc.ids.insert(varI.GetName());

	//	Variable varJ;
	//	varJ.SetName("j");
	//	varJ.SetValue(4.0);
	//	calc.vars.emplace(varJ.GetName(), varJ);
	//	calc.ids.insert(varJ.GetName());

	//	Function fnA;
	//	fnA.SetName("A");
	//	fnA.SetOperator('+');
	//	fnA.SetFirstIdValue(varX);
	//	fnA.SetSecondIdValue(varY);
	//	calc.fns.push_back(fnA);
	//	calc.ids.insert(fnA.GetName());

	//	Function fnB;
	//	fnB.SetName("B");
	//	fnB.SetOperator('+');
	//	fnB.SetFirstIdValue(varI);
	//	fnB.SetSecondIdValue(varJ);
	//	calc.fns.push_back(fnB);
	//	calc.ids.insert(fnB.GetName());

	//	Function fnC;
	//	fnC.SetName("C");
	//	fnC.SetOperator('+');
	//	fnC.SetFirstIdValue(fnA);
	//	fnC.SetSecondIdValue(fnB);
	//	calc.fns.push_back(fnC);
	//	calc.ids.insert(fnC.GetName());

	//	CHECK(calc.Calculate("C") == 10.0);
	//}

	//SECTION("Function contains two Function args that contains pair of Variables for each should return sum of them after one of Variables was changed")
	//{
	//	Calculator calc;

	//	Variable varX;
	//	varX.SetName("x");
	//	varX.SetValue(1.0);
	//	calc.vars.emplace(varX.GetName(), varX);
	//	calc.ids.insert(varX.GetName());

	//	Variable varY;
	//	varY.SetName("y");
	//	varY.SetValue(2.0);
	//	calc.vars.emplace(varY.GetName(), varY);
	//	calc.ids.insert(varY.GetName());

	//	Variable varI;
	//	varI.SetName("i");
	//	varI.SetValue(3.0);
	//	calc.vars.emplace(varI.GetName(), varI);
	//	calc.ids.insert(varI.GetName());

	//	Variable varJ;
	//	varJ.SetName("j");
	//	varJ.SetValue(4.0);
	//	calc.vars.emplace(varJ.GetName(), varJ);
	//	calc.ids.insert(varJ.GetName());

	//	Function fnA;
	//	fnA.SetName("A");
	//	fnA.SetOperator('+');
	//	fnA.SetFirstIdValue(varX);
	//	fnA.SetSecondIdValue(varY);
	//	calc.fns.push_back(fnA);
	//	calc.ids.insert(fnA.GetName());

	//	Function fnB;
	//	fnB.SetName("B");
	//	fnB.SetOperator('+');
	//	fnB.SetFirstIdValue(varI);
	//	fnB.SetSecondIdValue(varJ);
	//	calc.fns.push_back(fnB);
	//	calc.ids.insert(fnB.GetName());

	//	Function fnC;
	//	fnC.SetName("C");
	//	fnC.SetOperator('+');
	//	fnC.SetFirstIdValue(fnA);
	//	fnC.SetSecondIdValue(fnB);
	//	calc.fns.push_back(fnC);
	//	calc.ids.insert(fnC.GetName());

	//	varJ.SetValue(5.0);

	//	CHECK(calc.Calculate("C") == 11.0);
	//}

//	SECTION("Fibbonachi testing")
//	{
//		Calculator calc;
//
//		Variable v0;
//		v0.SetName("v0");
//		v0.SetValue(0.0);
//		calc.vars.emplace(v0.GetName(), v0);
//		calc.ids.insert(v0.GetName());
//
//		Variable v1;
//		v1.SetName("v1");
//		v1.SetValue(1.0);
//		calc.vars.emplace(v1.GetName(), v1);
//		calc.ids.insert(v1.GetName());
//
//		Function fb0;
//		fb0.SetName("fb0");
//		fb0.SetFirstIdValue(calc.vars["v0"]);
//		calc.fns.emplace(fb0.GetName(), fb0);
//		calc.ids.insert(fb0.GetName());
//
//		Function fb1;
//		fb1.SetName("fb1");
//		fb1.SetFirstIdValue(calc.vars["v1"]);
//		calc.fns.emplace(fb1.GetName(), fb1);
//		calc.ids.insert(fb1.GetName());
//
//		Function fb2;
//		fb2.SetName("fb2");
//		fb2.SetOperator('+');
//		fb2.SetFirstIdValue(calc.fns["fb0"]);
//		fb2.SetSecondIdValue(calc.fns["fb1"]);
//
//
//		calc.fns.emplace(fb2.GetName(), fb2);
//		calc.ids.insert(fb2.GetName());
//		CHECK(calc.Calculate(fb2.GetName()) == 1.0);
//
//		Function fb3;
//		fb3.SetName("fb3");
//		fb3.SetOperator('+');
//
//		fb3.SetFirstIdValue(calc.fns["fb1"]);
//		fb3.SetSecondIdValue(calc.fns["fb2"]);
//
//
//		calc.fns.emplace(fb3.GetName(), fb3);
//		calc.ids.insert(fb3.GetName());
//
//
//		CHECK(calc.Calculate(fb3.GetName()) == 2.0);
//	}
//}

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

		for (int i = 2; i < 4; ++i)
		{
			Function fn;
			std::string fnName = "fb" + std::to_string(i);
			fn.SetName(fnName);
			fn.SetOperator('+');
			fn.SetFirstIdValue(*calc.GetFunction("fb" + std::to_string(i - 1)));
			fn.SetSecondIdValue(*calc.GetFunction("fb" + std::to_string(i - 2)));

			calc.AddFunction(fn);
		}
		CHECK(calc.Calculate("fb3") == 2.0);
		calc.GetVariable("v0")->SetValue(5.0);
		CHECK(calc.Calculate("fb3") == 7.0);
	}
}

