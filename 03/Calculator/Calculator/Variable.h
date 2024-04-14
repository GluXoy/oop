#pragma once
#include <string>

class Variable
{
public:
	Variable() {};
	Variable(std::string name) : m_name(name) {};

	std::string m_name;
	mutable double m_value = NAN;
	bool isInitialized = false;
};