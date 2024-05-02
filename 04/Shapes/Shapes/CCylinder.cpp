#define _USE_MATH_DEFINES
#include "CCylinder.h"
#include <cmath>
#include <sstream>
#include <iomanip>

CCylinder::CCylinder(double density, double height, double radius)
	: CBody("Cylinder", density),
	m_radius(radius),
	m_height(height)
{
}

double CCylinder::GetBaseRadius() const
{
	return m_radius;
}

double CCylinder::GetHeight() const
{
	return m_height;
}

double CCylinder::GetVolume() const
{
	return (pow(m_radius, 2) * M_PI) * m_height;
}

void CCylinder::AppendProperties(std::ostream& strm) const
{
	strm << "\tbase radius = " << GetBaseRadius() << std::endl
		<< "\theight = " << GetHeight() << std::endl;
}