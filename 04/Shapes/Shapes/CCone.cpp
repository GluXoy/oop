#define _USE_MATH_DEFINES
#include "CCone.h"
#include <cmath>
#include <sstream>
#include <iomanip>

CCone::CCone(double density, double height, double radius)
	: CBody("Cone", density),
	m_radius(radius),
	m_height(height)
{
}

double CCone::GetVolume() const
{
	return (pow(m_radius, 2) * M_PI) * m_height * 1 / 3;
}

double CCone::GetBaseRadius() const
{
	return m_radius;
}

double CCone::GetHeight() const
{
	return m_height;
}

void CCone::AppendProperties(std::ostream& strm) const
{
	strm << "\tbase radius = " << GetBaseRadius() << std::endl
		<< "\theight = " << GetHeight() << std::endl;
}