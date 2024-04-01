#include "Function.h"
#include <cmath>

void Function::SetFirstIdValue(double* id) 
{
	m_firstId = id;
}

void Function::SetSecondIdValue(double* id)
{
	m_secondId = id;
}

void Function::SetOperator(char op)
{
	m_operator = op;
}

char Function::GetOperator() const
{
	return m_operator;
}

//double Function::GetFirstIdValue() const
//{
//	
//}
//
//double Function::GetSecondIdValue() const
//{
//	
//}

void Function::SetName(std::string name)
{
	m_name = name;
}

std::string Function::GetName() const
{
	return m_name;
}

double Function::Result() const
{
	if (m_firstId != nullptr && m_secondId != nullptr)
	{
		return
			m_operator == '*' ? (*m_firstId) * (*m_secondId) :
			m_operator == '+' ? (*m_firstId) + (*m_secondId) :
			m_operator == '-' ? (*m_firstId) - (*m_secondId) :
			*m_firstId / *m_secondId;
	}

	return m_firstId == nullptr ? NAN : *m_firstId;
}

Function::Function()
{
	m_firstId = nullptr;
	m_secondId = nullptr;
}