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
	using VarMap = std::map<std::string, Variable>;
	using FnMap = std::map<std::string, Function>;
	using IdSet = std::set<std::string>;

	VarMap vars;
	FnMap fns;
	IdSet ids;

	double Calculate(std::string idName); // const


private:
	double Operate(double val1, double val2, char op);
	double CalculateFn(std::variant<Variable*, Function*> f);
	
	//инкапсулировать данные
	//нужны ли? 
	//void AddFnToSet(Function fn);
	//void AddVarToSet(Variable var);
	//---------
	//void ChangeFn(Function& fn);
	//void ChangeVar(Variable var);
};