#pragma once
#include "Function.h"
#include "Variable.h"
#include "Calculator.h"

class CalculatorPresenter
{
public:
	bool InputHandler();
	void Print(std::string idName);
	void PrintVars();
	//void PrintFns();
	CalculatorPresenter(Calculator& calculator);
	Calculator& m_calc;
private:
	Function CreateFunction();
	Variable CreateVariable();
	bool IsValidIdentifier(const std::string& identifier);
	bool ParseVarStatement(const std::string& statement, Variable& var);
	bool ParseLetStatement(const std::string& statement, Variable& var);
	bool ParseFnStatement(const std::string& statement, Function& fn);
	void CheckIfIdWasDeclared(std::string idName);
	void SetIdValue(Function& fn, std::string idName, int idPos);
	bool WasIdDeclared(std::string idName);
};
