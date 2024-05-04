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
	double GetVolume() const override;
private:
	void UpdateFields();
	void AppendProperties(std::ostream& strm) const override;
	std::vector<std::unique_ptr<CBody>> m_childs;
	double m_volume = 0; // исправить: при добавлении детей сделать модификацию родителя для CCompound
};