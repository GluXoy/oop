#pragma once
#include <string>

class Function
{
public:
	bool isInitialized = false;
	void SetFirstIdValue(double* id);
	void SetSecondIdValue(double* id);
	void SetOperator(char op);
	char GetOperator() const;
	//double GetFirstIdValue() const;
	//double GetSecondIdValue() const;
	void SetName(std::string name); 
	std::string GetName() const;
	double Result() const;
	Function();
	bool operator<(const Function& other) const
	{
		return m_name < other.m_name;
	}
private:
	std::string m_name;
	double* m_firstId;
	double* m_secondId;
	char m_operator = '\0';
};