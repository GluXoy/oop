#pragma once
#include <set>
#include <functional>
#include "Function.h"
#include "Variable.h"

class Calculator
{
public:
	using VarSet = std::set<Variable>;
	using FnSet = std::set<Function>;
	using IdSet = std::set<std::string>;
	VarSet vars;
	FnSet fns;
	IdSet ids;

	//нужны ли? 
	//void AddFnToSet(Function fn);
	//void AddVarToSet(Variable var);
	//---------
	//void ChangeFn(Function& fn);
	//void ChangeVar(Variable var);
};