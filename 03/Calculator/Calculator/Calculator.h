#pragma once
#include <map>
#include <set>
#include <vector>
#include "Function.h"
#include "Variable.h"


class Calculator
{
public:
	double Calculate(std::string idName) const;
	void AddFunction(Function& fn);
	void AddVariable(Variable& var);
	void ChangeVariable(std::string idName, double value);
	const Function* GetFunction(std::string idName) const;
	const Variable* GetVariable(std::string idName) const;
	bool WasIdDeclared(std::string idName) const;
	bool IsVariableDeclared(std::string idName) const;
	bool IsFunctionDeclared(std::string idName) const;
	void PrintFns() const;
	void PrintVars() const;
private:
	using VarMap = std::map<std::string, Variable>;
	using FnMap = std::map<std::string, Function>;
	using IdSet = std::set<std::string>;

	std::vector<std::string> fnIds;

	VarMap vars;
	FnMap fns;
	IdSet ids;

	double Operate(double val1, double val2, char op);
	void ChangeFnResults();
};