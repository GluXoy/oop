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

bool CalculatorPresenter::ParseVarStatement(const std::string& statement)
{
    std::regex varRegex("^var\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*$");
    std::smatch match;

    if (!std::regex_match(statement, match, varRegex))
    {
        return false;
    }

    Variable var;

    if (m_calc.IsVariableDeclared(match[1]))
    {
        throw std::invalid_argument("This id was declared before!");
    }

    var.SetName(match[1]);
    var.SetValue(NAN);
    m_calc.AddVariable(var);
    return true;
}


bool CalculatorPresenter::ParseLetStatement(const std::string& statement)
{
    std::regex letRegex("^let\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*([a-zA-Z_][a-zA-Z0-9_]*|[0-9]+\\.[0-9]+)\\s*$");
    std::smatch match;
    if (!std::regex_match(statement, match, letRegex))
    {
        return false;
    }
    Variable var;

    std::string letName = match[1];
    std::string letValue = match[2];

    if (m_calc.IsVariableDeclared(letValue))
    {
        if (m_calc.IsVariableDeclared(letName))
        {
            m_calc.ChangeVariable(letName, m_calc.GetVariable(letValue)->GetValue());
        }
        else
        {
            var.SetName(letName);
            var.SetValue(m_calc.GetVariable(letValue)->GetValue());
            m_calc.AddVariable(var);
        }
        //m_calc.ChangeFnResults();
        return true;
    }

    if (IsValidIdentifier(letValue))
    {
        throw std::runtime_error("Unknown identifier name!");
    }

    double value = std::stod(letValue);

    if (m_calc.IsVariableDeclared(letName))
    {
        m_calc.ChangeVariable(letName, value);
    }
    else
    {
        var.SetName(letName);
        var.SetValue(value);
        m_calc.AddVariable(var);
    }
    //m_calc.ChangeFnResults();
    return true;
}

void CalculatorPresenter::SetIdValue(Function& fn, std::string idName, int idPos)
{
    if (m_calc.IsFunctionDeclared(idName))
    {
        idPos == 1 ? fn.SetFirstIdValue(*m_calc.GetFunction(idName)) : fn.SetSecondIdValue(*m_calc.GetFunction(idName));
    }
    else if (m_calc.IsVariableDeclared(idName))
    {
        idPos == 1 ? fn.SetFirstIdValue(*m_calc.GetVariable(idName)) : fn.SetSecondIdValue(*m_calc.GetVariable(idName));
    }
    else
    {
        throw std::invalid_argument("Identifier wasn't find!");
    }
}

bool CalculatorPresenter::ParseFnStatement(const std::string& statement)
{
    std::regex fnRegex("^fn\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\s*(?:([+\\-*/])\\s*([a-zA-Z_][a-zA-Z0-9_]*))?\\s*$");
    std::smatch match;

    if (!std::regex_match(statement, match, fnRegex))
    {
        return false;
    }

    Function fn;
    std::string fnName = match[1];
    std::string firstId = match[2];
    std::string operation = match[3];
    std::string secondId = match[4];

    if (m_calc.WasIdDeclared(fnName))
    {
        throw std::invalid_argument("This id was declared before!");
    }

    if (!m_calc.WasIdDeclared(firstId))
    {
        throw std::invalid_argument("Unknown identifier - " + firstId + " - in the expression!");
    }

    if (!operation.empty() && !secondId.empty())
    {
        if (!m_calc.WasIdDeclared(secondId))
        {
            throw std::invalid_argument("Unknown identifier - " + secondId + " - in the expression!");
        }

        fn.SetOperator(operation[0]);
        SetIdValue(fn, secondId, 2);
    }

    fn.SetName(fnName);
    SetIdValue(fn, firstId, 1);

    m_calc.AddFunction(fn);
    return true;
}

bool CalculatorPresenter::InputHandler()
{
    std::string commandLine;
    std::getline(std::cin, commandLine);

    if (commandLine.substr(0, 6) == "Print ")
    {
        std::string idName = commandLine.substr(6);
        Print(idName);
        return true;
    }
    else if (commandLine == "PrintVars")
    {
        m_calc.PrintVars();
        return true;
    }
    else if (commandLine == "PrintFns")
    {
        m_calc.PrintFns();
        return true;
    }
    else
    {
        return
            ParseVarStatement(commandLine) ? true :
            ParseLetStatement(commandLine) ? true :
            ParseFnStatement(commandLine);
    }
}


void CalculatorPresenter::Print(std::string idName)
{
    if (m_calc.WasIdDeclared(idName))
    {
        std::cout << m_calc.Calculate(idName) << std::endl;
    }
    else
    {
        throw std::invalid_argument("Unknown Id!");
    }
}