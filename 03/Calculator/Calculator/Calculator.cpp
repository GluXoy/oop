#include "Calculator.h"
#include <string>
#include "Variable.h"
#include "Function.h"
#include <variant>
#include <vector>
#include <iostream>

bool Calculator::IsVariableDeclared(std::string idName) const
{
    if (vars.find(idName) != vars.end())
    {
        return true;
    }
    return false;
}

bool Calculator::IsFunctionDeclared(std::string idName) const
{
    if (fns.find(idName) != fns.end())
    {
        return true;
    }
    return false;
}

bool Calculator::WasIdDeclared(std::string idName) const
{
    if (ids.find(idName) == ids.end())
    {
        return false;
    }
    return true;
}

void Calculator::AddFunction(Function& fn)
{
    if (ids.find(fn.GetName()) != ids.end())
    {
        throw std::invalid_argument("This id was declared before!");
    }
    fns.emplace(fn.GetName(), fn);
    ids.insert(fn.GetName());
}

void Calculator::AddVariable(Variable& var)
{
    if (ids.find(var.GetName()) != ids.end())
    {
        throw std::invalid_argument("This id was declared before!");
    }
    vars.emplace(var.GetName(), var);
    ids.insert(var.GetName());
}

Function* Calculator::GetFunction(std::string idName)
{
    return &fns[idName];
}

Variable* Calculator::GetVariable(std::string idName)
{
    return &vars[idName];
}

double Calculator::Operate(double val1, double val2, char op)
{ 
    switch (op)
    {
    case '*':
        return val1 * val2;
    case '+':
        return val1 + val2;
    case '-':
        return val1 - val2;
    case '/':
        return val1 / val2;
    default:
        return val1;
    }
}

double Calculator::CalculateFn(std::variant<Variable*, Function*> f)
{
    //если double 
    if (std::holds_alternative<Variable*>(f))
    {
        if (std::get<Variable*>(f) == nullptr)
        {
            return NAN;
        }
        return std::get<Variable*>(f)->GetValue();
    }
    
    //если Function
    Function* fn = std::get<Function*>(f);
    std::variant<Variable*, Function*> firstId = fn->GetFirstIdValue();
    std::variant<Variable*, Function*> secondId = fn->GetSecondIdValue();

    double val1 = CalculateFn(firstId);
    double val2 = CalculateFn(secondId);

    return Operate(val1, val2, fn->GetOperator());
}


double Calculator::Calculate(std::string idName)
{

    if (fns.find(idName) != fns.end())
    {
        std::variant<Variable*, Function*> firstId = fns[idName].GetFirstIdValue();
        std::variant<Variable*, Function*> secondId = fns[idName].GetSecondIdValue();
        double val1 = CalculateFn(firstId);
        double val2 = CalculateFn(secondId);

        return Operate(val1, val2, fns[idName].GetOperator());
        //return CalculateFn(&tempFunction);
    }


    if (vars.find(idName) != vars.end())
    {
        return vars[idName].GetValue();
    }

    throw std::invalid_argument("Unknown id!");
}