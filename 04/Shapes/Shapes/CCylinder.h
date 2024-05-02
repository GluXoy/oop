#pragma once

#include "CBody.h"

class CCylinder : public CBody
{
public:
	CCylinder(double density, double height, double radius);
	double GetBaseRadius() const;
	double GetHeight() const;
	double GetVolume() const override;
private:
	void AppendProperties(std::ostream& strm) const override;
	double m_height;
	double m_radius;
};