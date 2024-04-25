#pragma once
#include <string>
#include <variant>
#include "Variable.h"

class Function
{
public:
	void SetFirstIdValue(const Variable& id);
	void SetFirstIdValue(const Function& id);
	void SetSecondIdValue(const Function& id);
	void SetSecondIdValue(const Variable& id);
	void SetOperator(char op);
	char GetOperator() const;
	std::variant<const Variable*, const Function*> GetFirstIdValue() const;
	std::variant<const Variable*, const Function*> GetSecondIdValue() const;
	void SetName(std::string name); 
	std::string GetName() const;
	double GetResult() const;
	void SetResult(double res);


private:
	std::string m_name;
	std::variant<const Variable*, const Function*> m_firstId;
	std::variant<const Variable*, const Function*> m_secondId;
	mutable char m_operator = '\0';
	double m_result = NAN;
};