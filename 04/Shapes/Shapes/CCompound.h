#pragma once

#include "CBody.h"
#include <vector>
#include <memory>

class CCompound : public CBody
{
public:
	CCompound();
	bool AddChildBody(std::unique_ptr<CBody> child);
	size_t GetNumberOfChilds() const;
	std::vector<std::unique_ptr<CBody>> m_childs;
private:
	void UpdateFields();
	double GetVolume() const override;
	void AppendProperties(std::ostream& strm) const override;
	double m_volume = 0;
};