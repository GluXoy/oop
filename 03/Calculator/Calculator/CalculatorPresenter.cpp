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
            throw std::invalid_argument("This variable was declared before!");
        }
        var.SetName(match[1]);
        var.SetValue(NAN);
        m_calc.vars.insert(var);
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
        return false;
    }

    std::string letValue = match[2];
    if (m_calc.ids.find(letValue) != m_calc.ids.end())
    {
        for (auto& id : m_calc.vars)
        {
            if (id.GetName() == letValue)
            {
                if (WasIdDeclared(match[1]))
                {
                    for (auto& var : m_calc.vars)
                    {
                        if (var.GetName() == match[1])
                        {
                            var.SetValue(id.GetValue());
                        }
                    }
                }
                else
                {
                    var.SetName(match[1]);
                    var.SetValue(id.GetValue());
                    m_calc.vars.insert(var);
                    m_calc.ids.insert(var.GetName());
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
    var.SetName(match[1]);
    var.SetValue(value);
    m_calc.vars.insert(var);
    m_calc.ids.insert(var.GetName());

    return true;
}

void CalculatorPresenter::CheckIfIdWasDeclared(std::string idName)
{
    if (m_calc.ids.find(idName) == m_calc.ids.end())
    {
        throw std::invalid_argument("Unknown identifier - " + std::string(idName) + " - in the expression!");
    }
}

double CalculatorPresenter::GetValueFromId(std::string idName)
{
    for (const auto& fn : m_calc.fns)
    {
        if (fn.GetName() == idName)
        {
            return fn.Result();
        }
    }

    for (const auto& var : m_calc.vars)
    {
        if (var.GetName() == idName)
        {
            return var.GetValue();
        }
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
            throw std::invalid_argument("This function was declared before!");
        }

        CheckIfIdWasDeclared(match[2]);

        if (match.size() > 3)
        {
            CheckIfIdWasDeclared(match[4]);
            fn.SetOperator(match[3].str()[0]);
            double val2 = GetValueFromId(match[4]);
            fn.SetSecondIdValue(&val2);
        }
        fn.SetName(match[1]);

        double val1 = GetValueFromId(match[2]);
        fn.SetFirstIdValue(&val1);

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
    else if (commandLine == "PrintFns")
    {
        PrintFns();
        return true;
    }

    return
        ParseVarStatement(commandLine, var) ? true :
        ParseLetStatement(commandLine, var) ? true :
        ParseFnStatement(commandLine, fn);
}

void CalculatorPresenter::PrintVars()
{
    for (const auto& var : m_calc.vars)
    {
        std::cout << var.GetName() << " : " << var.GetValue() << std::endl;
    }
}

void CalculatorPresenter::PrintFns()
{
    for (const auto& fn : m_calc.fns)
    {
        std::cout << fn.GetName() << " : " << fn.Result() << std::endl;
    }
}
