#pragma once
#include <map>
#include <set>
#include "Function.h"
#include "Variable.h"
//убрать лишние include

// изменить ввод на int

class Calculator
{
public:
	double Calculate(std::string idName);
	void AddFunction(Function& fn);
	void AddVariable(Variable& var);
	Function* GetFunction(std::string idName);
	Variable* GetVariable(std::string idName);
	bool WasIdDeclared(std::string idName) const;
	bool IsVariableDeclared(std::string idName) const;
	bool IsFunctionDeclared(std::string idName) const;

private:
	using VarMap = std::map<std::string, Variable>;
	using FnMap = std::map<std::string, Function>;
	using IdSet = std::set<std::string>;

	VarMap vars;
	FnMap fns;
	IdSet ids;

	double Operate(double val1, double val2, char op);
	double CalculateFn(std::variant<Variable*, Function*> f);
};