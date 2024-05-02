#define _USE_MATH_DEFINES
#include "../Shapes/CBody.h"
#include <cmath>
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>
#include "CCompound.h"

CCompound::CCompound()
	: CBody("Compound", 0.0)
{
}

double CCompound::GetVolume() const
{
	return m_volume;
}

void CCompound::UpdateFields()
{
	double totalVolume = 0;
	double totalMass = 0;
	
	for (auto& child : m_childs)
	{
		totalVolume += child->GetVolume();
		totalMass += child->GetMass();
	}

	m_density = totalMass / totalVolume;
	m_volume = totalVolume;
}

bool CCompound::AddChildBody(std::unique_ptr<CBody> child)
{
	m_childs.push_back(std::move(child));
	UpdateFields();
	return true;
}

size_t CCompound::GetNumberOfChilds() const
{
	return m_childs.size();
}

void CCompound::AppendProperties(std::ostream& strm) const
{
	strm << "\tnumber of childs = " << GetNumberOfChilds() << std::endl;
}