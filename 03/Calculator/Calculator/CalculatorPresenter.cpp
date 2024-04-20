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
        var.SetName(match[1]);
        var.SetValue(NAN);
        m_calc.vars.emplace(var.GetName(), var);
        m_calc.ids.insert(var.GetName());

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

    if (m_calc.vars.find(letValue) != m_calc.vars.end())
    {
        if (m_calc.vars.find(match[1]) != m_calc.vars.end())
        {
            m_calc.vars[match[1]].SetValue(m_calc.vars[letValue].GetValue());
        }
        else
        {
            var.SetName(match[1]);
            var.SetValue(m_calc.vars[letValue].GetValue());
            m_calc.vars.emplace(var.GetName(), var);
            m_calc.ids.insert(var.GetName());
        }
        return true;
    }


    if (IsValidIdentifier(letValue))
    {
        throw std::runtime_error("Unknown identifier name!");
    }

    double value = std::stod(letValue);

    if (m_calc.vars.find(match[1]) != m_calc.vars.end())
    {
        m_calc.vars[match[1]].SetValue(value);
    }
    else
    {
        var.SetName(match[1]);
        var.SetValue(value);
        m_calc.vars.emplace(var.GetName(), var);
        m_calc.ids.insert(var.GetName());
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
    for (auto& f : m_calc.fns)
    {
        if (idName == f.GetName())
        {
            idPos == 1 ? fn.SetFirstIdValue(f) : fn.SetSecondIdValue(f);
            return;
        }
    }

    if (m_calc.vars.find(idName) != m_calc.vars.end())
    {
        idPos == 1 ? fn.SetFirstIdValue(m_calc.vars[idName]) : fn.SetSecondIdValue(m_calc.vars[idName]);
    }
}

bool CalculatorPresenter::ParseFnStatement(const std::string& statement)
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

        Function fn;
        m_calc.fns.push_back(fn);

        int firstPosId = 1;
        int secondPosId = 2;

        std::string operation = match[3];
        std::string secondId = match[4];
        if (!operation.empty() && !secondId.empty())
        {
            //поменять название на BreakIf..
            CheckIfIdWasDeclared(secondId);
            m_calc.fns[m_calc.fns.size() - 1].SetOperator(operation[0]);
            SetIdValue(m_calc.fns[m_calc.fns.size() - 1], secondId, secondPosId);
        }
        m_calc.fns[m_calc.fns.size() - 1].SetName(match[1]);

        SetIdValue(m_calc.fns[m_calc.fns.size() - 1], match[2], firstPosId);

        m_calc.ids.insert(m_calc.fns[m_calc.fns.size() - 1].GetName());
        return true;
    }
    return false;
}

bool CalculatorPresenter::InputHandler()
{
    std::string commandLine;
    std::getline(std::cin, commandLine);

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
        ParseFnStatement(commandLine) ? true :
        ParseVarStatement(commandLine, var) ? true :
        ParseLetStatement(commandLine, var);
}

void CalculatorPresenter::PrintVars()
{
    for (auto& var : m_calc.vars)
    {
        std::cout << var.first << " : " << var.second.GetValue() << std::endl;
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