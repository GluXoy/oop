#include "Function.h"
#include <cmath>

void Function::SetFirstIdValue(double* id) 
{
	m_firstId = new double;
	m_firstId = id;
}

void Function::SetFirstIdValue(Function& id)
{
	m_firstId = new Function;
	m_firstId = &id;
}

void Function::SetSecondIdValue(double* id)
{ 
	m_secondId = new double;
	m_secondId = id;
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

std::variant<double*, Function*> Function::GetFirstIdValue() const
{
	return m_firstId;
}

std::variant<double*, Function*> Function::GetSecondIdValue() const
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

//double Function::Result() const
//{
//	if (m_firstId != nullptr && m_secondId != nullptr)
//	{
//		return
//			// видимо придется добавить рекурсивный вывод Result если первый id или второй id - функции
//			m_operator == '*' ? (*m_firstId) * (*m_secondId) :
//			m_operator == '+' ? (*m_firstId) + (*m_secondId) :
//			m_operator == '-' ? (*m_firstId) - (*m_secondId) :
//			*m_firstId / *m_secondId;
//	}
//
//	return m_firstId == nullptr ? NAN : *m_firstId;
//}
