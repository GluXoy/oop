#include "Function.h"
#include "Variable.h"
#include <cmath>

void Function::SetFirstIdValue(Variable& id) 
{
	m_firstId = new Variable;
	m_firstId = &id;
}

void Function::SetFirstIdValue(Function& id)
{
	m_firstId = new Function;
	m_firstId = &id;
}

void Function::SetSecondIdValue(Variable& id)
{ 
	m_secondId = new Variable;
	m_secondId = &id;
}

void Function::SetSecondIdValue(Function& id)
{
	m_secondId = new Function;
	m_secondId = &id;
}

void Function::SetOperator(char op)
{
	m_operator = op;
}

char Function::GetOperator() const
{
	return m_operator;
}

std::variant<Variable*, Function*> Function::GetFirstIdValue() const
{
	return m_firstId;
}

std::variant<Variable*, Function*> Function::GetSecondIdValue() const
{
	return m_secondId;
}

void Function::SetName(std::string name)
{
	m_name = name;
}

std::string Function::GetName() const
{
	return m_name;
}
