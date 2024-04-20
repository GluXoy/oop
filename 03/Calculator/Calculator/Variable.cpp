#include "Variable.h"

std::string Variable::GetName() const
{
	return m_name;
}

double Variable::GetValue() const
{
	return m_value;
}

void Variable::SetName(std::string name)
{
	m_name = name;
}

void Variable::SetValue(double value)
{
	m_value = value;
}