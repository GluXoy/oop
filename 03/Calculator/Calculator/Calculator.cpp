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

    double val1 = NAN;
    if (std::holds_alternative<const Variable*>(fn.GetFirstIdValue()))
    {
        if (std::get<const Variable*>(fn.GetFirstIdValue()) == nullptr)
        {
            val1 = NAN;
        }
        else
        {
            val1 = std::get<const Variable*>(fn.GetFirstIdValue())->GetValue();
        }
    }
    else if (std::holds_alternative<const Function*>(fn.GetFirstIdValue()))
    {
        val1 = std::get<const Function*>(fn.GetFirstIdValue())->GetResult();
    }

    double val2 = NAN;
    if (std::holds_alternative<const Variable*>(fn.GetSecondIdValue()))
    {
        if (std::get<const Variable*>(fn.GetSecondIdValue()) == nullptr)
        {
            val2 = NAN;
        }
        else
        {
            val2 = std::get<const Variable*>(fn.GetSecondIdValue())->GetValue();
        }
    }
    else if (std::holds_alternative<const Function*>(fn.GetSecondIdValue()))
    {
        val2 = std::get<const Function*>(fn.GetSecondIdValue())->GetResult();
    }

    fn.SetResult(Operate(val1, val2, fn.GetOperator()));

    fns.emplace(fn.GetName(), fn);
    ids.insert(fn.GetName());
    fnIds.push_back(fn.GetName());
}

void Calculator::ChangeFnResults()
{
    for (auto& fnId : fnIds)
    {
        double val1 = NAN;
        double val2 = NAN;

        if (std::holds_alternative<const Variable*>(fns.at(fnId).GetFirstIdValue()))
        {
            if (std::get<const Variable*>(fns.at(fnId).GetFirstIdValue()) == nullptr)
            {
                val1 = NAN;
            }
            else
            {
                val1 = std::get<const Variable*>(fns.at(fnId).GetFirstIdValue())->GetValue();
            }
        }
        else if (std::holds_alternative<const Function*>(fns.at(fnId).GetFirstIdValue()))
        {
            val1 = std::get<const Function*>(fns.at(fnId).GetFirstIdValue())->GetResult();
        }

        if (std::holds_alternative<const Variable*>(fns.at(fnId).GetSecondIdValue()))
        {
            if (std::get<const Variable*>(fns.at(fnId).GetSecondIdValue()) == nullptr)
            {
                val2 = NAN;
            }
            else
            {
                val2 = std::get<const Variable*>(fns.at(fnId).GetSecondIdValue())->GetValue();
            }
        }
        else if (std::holds_alternative<const Function*>(fns.at(fnId).GetSecondIdValue()))
        {
            val2 = std::get<const Function*>(fns.at(fnId).GetSecondIdValue())->GetResult();
        }

        fns.at(fnId).SetResult(Operate(val1, val2, fns.at(fnId).GetOperator()));
    }
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

const Function* Calculator::GetFunction(std::string idName) const
{
    return &fns.at(idName);
}

const Variable* Calculator::GetVariable(std::string idName) const
{
    return &vars.at(idName);
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

//double Calculator::CalculateFn(std::variant<Variable*, Function*> f)
//{
//    //если double 
//    if (std::holds_alternative<Variable*>(f))
//    {
//        if (std::get<Variable*>(f) == nullptr)
//        {
//            return NAN;
//        }
//        return std::get<Variable*>(f)->GetValue();
//    }
//    
//    //если Function
//    Function* fn = std::get<Function*>(f);
//    std::variant<Variable*, Function*> firstId = fn->GetFirstIdValue();
//    std::variant<Variable*, Function*> secondId = fn->GetSecondIdValue();
//
//    double val1 = CalculateFn(firstId);
//    double val2 = CalculateFn(secondId);
//
//    return Operate(val1, val2, fn->GetOperator());
//}
//
//
//double Calculator::Calculate(std::string idName)
//{
//    if (fns.find(idName) != fns.end())
//    {
//        std::variant<Variable*, Function*> firstId = fns[idName].GetFirstIdValue();
//        std::variant<Variable*, Function*> secondId = fns[idName].GetSecondIdValue();
//        double val1 = CalculateFn(firstId);
//        double val2 = CalculateFn(secondId);
//
//        return Operate(val1, val2, fns[idName].GetOperator());
//    }
//
//
//    if (vars.find(idName) != vars.end())
//    {
//        return vars[idName].GetValue();
//    }
//
//    throw std::invalid_argument("Unknown id!");
//}

void Calculator::ChangeVariable(std::string idName, double value)
{
    vars.at(idName).SetValue(value);
    ChangeFnResults();
}

double Calculator::Calculate(std::string idName) const
{
    if (fns.find(idName) != fns.end())
    {
        return GetFunction(idName)->GetResult();
    }

    if (vars.find(idName) != vars.end())
    {
        return vars.at(idName).GetValue();
    }

    throw std::invalid_argument("Unknown id!");
}

void Calculator::PrintFns() const
{
    for (const auto& [name, fn] : fns)
    {
        std::cout << name << " : " << fn.GetResult() << std::endl;
    }
}

void Calculator::PrintVars() const
{
    for (const auto& [name, var] : vars)
    {
        std::cout << name << " : " << var.GetValue() << std::endl;
    }
}
