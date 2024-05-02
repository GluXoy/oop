#define _USE_MATH_DEFINES
#include "CParallelepiped.h"
#include <cmath>
#include <sstream>
#include <iomanip>

CParallelepiped::CParallelepiped(double density, double width, double height, double depth)
	: CBody("Parallelepiped", density),
	m_height(height),
	m_width(width),
	m_depth(depth)
{
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

double CParallelepiped::GetVolume() const
{
	return m_width * m_depth * m_height;
}

void CParallelepiped::AppendProperties(std::ostream& strm) const
{
	strm << "\twidth = " << GetWidth() << std::endl
		<< "\theight = " << GetHeight() << std::endl
		<< "\tdepth = " << GetDepth() << std::endl;
}