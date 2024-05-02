#pragma once

#include "CBody.h"
	
class CParallelepiped : public CBody
{
public:
	CParallelepiped(double density, double width, double height, double depth);
	double GetHeight() const;
	double GetWidth() const;
	double GetDepth() const;
	double GetVolume() const override;
private:
	void AppendProperties(std::ostream& strm) const override;
	double m_height;
	double m_width;
	double m_depth;
};