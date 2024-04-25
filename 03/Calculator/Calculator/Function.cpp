#include "Function.h"
#include "Variable.h"
#include <cmath>

void Function::SetFirstIdValue(const Variable& id)
{
	m_firstId = &id;
}

void Function::SetFirstIdValue(const Function& id)
{
	m_firstId = &id;
}

void Function::SetSecondIdValue(const Variable& id)
{ 
	m_secondId = &id;
}

void Function::SetSecondIdValue(const Function& id)
{
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

std::variant<const Variable*, const Function*> Function::GetFirstIdValue() const
{
	return m_firstId;
}

std::variant<const Variable*, const Function*> Function::GetSecondIdValue() const
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

double Function::GetResult() const
{
	return m_result;
}

void Function::SetResult(double res)
{
	m_result = res;
}
