#pragma once
#include <set>
#include <functional>
#include "Function.h"
#include "Variable.h"
#include <unordered_set>

class Calculator
{
public:

	struct FunctionComparator
	{
		bool operator()(const Function& f1, const Function& f2) const
		{
			return f1.GetName() < f2.GetName();
		}
	};

	struct VariableComparator
	{
		bool operator()(const Variable& v1, const Variable& v2) const
		{
			return v1.m_name < v2.m_name;
		}
	};


	using VarSet = std::set<Variable, VariableComparator>;
	using FnSet = std::set<Function, FunctionComparator>;
	using IdSet = std::set<std::string>;
	VarSet vars;
	FnSet fns;
	IdSet ids;

	double Calculate(std::string idName);
private:
	double Operate(double val1, double val2, char op);
	double CalculateFn(std::variant<double*, Function*> f);
	//нужны ли? 
	//void AddFnToSet(Function fn);
	//void AddVarToSet(Variable var);
	//---------
	//void ChangeFn(Function& fn);
	//void ChangeVar(Variable var);
};