#pragma once
#include <string>

class Variable
{
public:
	std::string GetName() const;
	double GetValue() const;
	void SetName(std::string name);
	void SetValue(double value);
	bool operator<(const Variable& other) const
	{
		return m_name < other.m_name;
	}
private:
	std::string m_name;
	double m_value = NAN;
	bool isInitialized = false;
};