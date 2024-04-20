#pragma once
#include <string>

class Variable
{
public:
	std::string GetName() const;
	double GetValue() const;
	void SetName(std::string name);
	void SetValue(double value);

	Variable() {};

private:
	std::string m_name;
	mutable double m_value = NAN;
};