#pragma once
#include <string>
#include <variant>
#include "Variable.h"

class Function
{
public:
	bool isInitialized = false;
	void SetFirstIdValue(Variable& id);
	void SetFirstIdValue(Function& id);
	void SetSecondIdValue(Function& id);
	void SetSecondIdValue(Variable& id);
	void SetOperator(char op);
	char GetOperator() const;
	std::variant<Variable*, Function*> GetFirstIdValue() const;
	std::variant<Variable*, Function*> GetSecondIdValue() const;
	void SetName(std::string name); 
	std::string GetName() const;
	//bool operator<(const Function& other) const
	//{
	//	return m_name < other.m_name;
	//}


private:
	std::string m_name;
	std::variant<Variable*, Function*> m_firstId;
	std::variant<Variable*, Function*> m_secondId;
	mutable char m_operator = '\0';
};