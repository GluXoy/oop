#pragma once
#include <string>
#include <iostream>
class CBody
{
public:
	CBody(const std::string& type, double density);

	double GetDensity() const;
	virtual double GetVolume() const = 0;
	double GetMass() const;
	std::string ToString() const;

	//вы€снить дл€ чего он нужен
	virtual ~CBody() { std::cout << "~CBody()" << std::endl; };
protected:
	double m_density;
private:
	virtual void AppendProperties(std::ostream& strm) const = 0;
	std::string m_type;
};