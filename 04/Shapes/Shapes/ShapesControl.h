#pragma once

#include "CBody.h"
#include "CSphere.h"
#include "CCone.h"
#include "CParallelepiped.h"
#include "CCylinder.h"
#include "CCompound.h"
#include <vector>
#include <memory>
#include <functional>

class ShapesControl
{
public:
	bool InputHandler();
	std::unique_ptr<CSphere> CreateSphere();
	std::unique_ptr<CCone> CreateCone();
	std::unique_ptr<CCylinder> CreateCylinder();
	std::unique_ptr<CParallelepiped> CreateParallelepiped();
	std::unique_ptr<CCompound> CreateCompound();
	void ShowHeaviestBody() const;
	void ShowLightestBodyInTheWater() const;
	void PrintShapesInfo() const;
	bool AddShape(std::unique_ptr<CBody> shape);
private:
	bool ShapeIdentifier(std::function<bool(std::unique_ptr<CBody>)> addShapeFunc);
	double InputDensity() const;
	double InputRadius() const;
	double InputHeight() const;
	double InputWidth() const;
	double InputDepth() const;
	int	SelectionOfShapesList() const;
	double GiveForceValue(double density, double volume) const;
	std::vector<std::unique_ptr<CBody>> m_shapes;
};