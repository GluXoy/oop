#pragma once
#include <string>

class CBody
{
public:
	CBody(const std::string& type, double density);
	CBody() = delete;

	double GetDensity() const;
	virtual double GetVolume() const = 0;
	double GetMass() const;
	std::string ToString() const;

	virtual ~CBody() = default;
protected:
	double m_density;
private:
	virtual void AppendProperties(std::ostream& strm) const = 0;
	std::string m_type;
};