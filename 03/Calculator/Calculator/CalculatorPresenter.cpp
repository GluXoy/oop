#include "Calculator.h"
#include "CalculatorPresenter.h"
#include <string>
#include <iostream>
#include <sstream>
#include <regex>

CalculatorPresenter::CalculatorPresenter(Calculator& calculator) : m_calc(calculator)
{
}

bool CalculatorPresenter::IsValidIdentifier(const std::string& identifier)
{
    std::regex identifierRegex("^[a-zA-Z_][a-zA-Z0-9_]*$");
    return std::regex_match(identifier, identifierRegex);
}

bool CalculatorPresenter::ParseVarStatement(const std::string& statement, Variable& var)
{
    std::regex varRegex("^var\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*$");
    std::smatch match;
    if (std::regex_match(statement, match, varRegex))
    {
        if (m_calc.ids.find(match[1]) != m_calc.ids.end())
        {
            throw std::invalid_argument("This id was declared before!");
        }
        var.m_name = match[1];
        var.m_value = NAN;
        m_calc.vars.insert(var);
        m_calc.ids.insert(var.m_name);

        return true;
    }
    return false;
}

bool CalculatorPresenter::WasIdDeclared(std::string idName)
{
    if (m_calc.ids.find(idName) == m_calc.ids.end())
    {
        return false;
    }
    return true;
}

bool CalculatorPresenter::ParseLetStatement(const std::string& statement, Variable& var)
{
    std::regex letRegex("^let\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*([a-zA-Z_][a-zA-Z0-9_]*|[0-9]+\\.[0-9]+)\\s*$");
    std::smatch match;
    if (!std::regex_match(statement, match, letRegex))
    {
        std::cout << "Incorrect signable format!" << std::endl;
        return false;
    }

    std::string letValue = match[2];
    if (m_calc.ids.find(letValue) != m_calc.ids.end())
    {
        for (auto& id : m_calc.vars)
        {
            if (id.m_name == letValue)
            {
                auto it = m_calc.vars.find(Variable(match[1]));
                if (it != m_calc.vars.end())
                {
                    it->m_value = id.m_value;
                }
                else
                {
                    var.m_name = match[1];
                    var.m_value = id.m_value;
                    m_calc.vars.insert(var);
                    m_calc.ids.insert(var.m_name);
                }
                return true;
            }
        }
    }

    if (IsValidIdentifier(letValue))
    {
        throw std::runtime_error("Unknown identifier name!");
    }

    double value = std::stod(letValue);

    auto it = m_calc.vars.find(Variable(match[1]));
    if (it != m_calc.vars.end())
    {
        it->m_value = value;
    }
    else
    {
        var.m_name = match[1];
        var.m_value = value;
        m_calc.vars.insert(var);
        m_calc.ids.insert(var.m_name);
    }

    return true;
}

void CalculatorPresenter::CheckIfIdWasDeclared(std::string idName)
{
    if (m_calc.ids.find(idName) == m_calc.ids.end())
    {
        throw std::invalid_argument("Unknown identifier - " + std::string(idName) + " - in the expression!");
    }
}

void CalculatorPresenter::SetIdValue(Function& fn, std::string idName, int idPos)
{
    auto it = m_calc.fns.find(Function(idName));

    if (it != m_calc.fns.end())
    {
        Function tempFunction = *it;
        m_calc.fns.erase(it);
        idPos == 1 ? fn.SetFirstIdValue(&tempFunction) : fn.SetSecondIdValue(&tempFunction);
        m_calc.fns.insert(tempFunction);
    }

    auto it2 = m_calc.vars.find(Variable(idName));

    if (it2 != m_calc.vars.end())
    {
        idPos == 1 ? fn.SetFirstIdValue(&it2->m_value) : fn.SetSecondIdValue(&it2->m_value);
    }
}

bool CalculatorPresenter::ParseFnStatement(const std::string& statement, Function& fn)
{
    std::regex fnRegex("^fn\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\s*(?:([+\\-*/])\\s*([a-zA-Z_][a-zA-Z0-9_]*))?\\s*$");
    std::smatch match;
    if (std::regex_match(statement, match, fnRegex))
    {
        if (m_calc.ids.find(match[1]) != m_calc.ids.end())
        {
            throw std::invalid_argument("This id was declared before!");
        }

        //поменять название на BreakIf..
        CheckIfIdWasDeclared(match[2]);

        int firstPosId = 1;
        int secondPosId = 2;

        std::string operation = match[3];
        std::string secondId = match[4];
        if (!operation.empty() && !secondId.empty())
        {
            //поменять название на BreakIf..
            CheckIfIdWasDeclared(secondId);
            fn.SetOperator(operation[0]);
            SetIdValue(fn, secondId, secondPosId);
        }
        fn.SetName(match[1]);

        SetIdValue(fn, match[2], firstPosId);

        m_calc.fns.insert(fn);
        m_calc.ids.insert(fn.GetName());
        return true;
    }
    return false;
}

bool CalculatorPresenter::InputHandler()
{
    std::string commandLine;
    std::getline(std::cin, commandLine);

    Function fn;
    Variable var;

    if (commandLine == "PrintVars")
    {
        PrintVars();
        return true;
    }
    else if (commandLine.substr(0, 6) == "Print ")
    {
        std::string idName = commandLine.substr(6);
        Print(idName);
        return true;
    }
    //else if (commandLine == "PrintFns")
    //{
    //    PrintFns();
    //    return true;
    //}

    return
        ParseVarStatement(commandLine, var) ? true :
        ParseLetStatement(commandLine, var) ? true :
        ParseFnStatement(commandLine, fn);
}

void CalculatorPresenter::PrintVars()
{
    for (const auto& var : m_calc.vars)
    {
        std::cout << var.m_name << " : " << var.m_value << std::endl;
    }
}

//void CalculatorPresenter::PrintFns()
//{
//    for (const auto& fn : m_calc.fns)
//    {
//        std::cout << fn.GetName() << " : " << fn.Result() << std::endl;
//    }
//}


void CalculatorPresenter::Print(std::string idName)
{
    if (m_calc.ids.find(idName) != m_calc.ids.end())
    {
        std::cout << m_calc.Calculate(idName) << std::endl;
    }
    else
    {
        throw std::invalid_argument("Unknown Id!");
    }
}