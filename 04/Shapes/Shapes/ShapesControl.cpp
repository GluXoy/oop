#include <iostream>
#include <memory>
#include "CBody.h"
#include "CSphere.h"
#include "CCone.h"
#include "CParallelepiped.h"
#include "CCylinder.h"
#include "CCompound.h"
#include "ShapesControl.h"
#include <functional>

void ShapesControl::ShowHeaviestBody() const
{
    if (m_shapes.size() == 0)
    {
        std::cout << "No shapes added!" << std::endl << std::endl;
        return;
    }

    size_t tempInd = 0;
    double tempMass = 0;
    for (size_t i = 0; i < m_shapes.size(); i++)
    {
        if (m_shapes[i]->GetMass() > tempMass)
        {
            tempMass = m_shapes[i]->GetMass();
            tempInd = i;
        }
    }
    std::cout << "The heaviest body - ";
    std::cout << m_shapes[tempInd]->ToString() << std::endl;
}

double ShapesControl::GiveForceValue(double density, double volume) const
{
    return (density - 1000.0) * 9.8 * volume;
}

void ShapesControl::ShowLightestBodyInTheWater() const
{
    if (m_shapes.size() == 0)
    {
        std::cout << "No shapes added!" << std::endl << std::endl;
        return;
    }

    size_t tempInd = 0;
    double tempWeight = -INFINITY;
    for (size_t i = 0; i < m_shapes.size(); i++)
    {
        if (GiveForceValue(m_shapes[i]->GetDensity(), m_shapes[i]->GetVolume()) > tempWeight)
        {
            tempWeight = GiveForceValue(m_shapes[i]->GetDensity(), m_shapes[i]->GetVolume());
            tempInd = i;
        }
    }

    std::cout << "The lightest body in the water - ";
    std::cout << m_shapes[tempInd]->ToString() << std::endl;
}

double ShapesControl::InputDensity() const
{
    double density = 0;
    std::cout << "Enter density: ";
    std::cin >> density;
    return density;
}

double ShapesControl::InputRadius() const
{
    double radius = 0;
    std::cout << "Enter radius: ";
    std::cin >> radius;
    return radius;
}

double ShapesControl::InputHeight() const
{
    double height = 0;
    std::cout << "Enter height: ";
    std::cin >> height;
    return height;
}

double ShapesControl::InputWidth() const
{
    double width = 0;
    std::cout << "Enter width: ";
    std::cin >> width;
    return width;
}

double ShapesControl::InputDepth() const
{
    double depth = 0;
    std::cout << "Enter depth: ";
    std::cin >> depth;
    return depth;
}


std::unique_ptr<CSphere> ShapesControl::CreateSphere()
{   
    auto sphere = std::make_unique<CSphere>(InputDensity(), InputRadius());
    return sphere;
}

std::unique_ptr<CCone> ShapesControl::CreateCone()
{
    auto cone = std::make_unique<CCone>(InputDensity(), InputHeight(), InputRadius());
    return cone;
}

std::unique_ptr<CCylinder> ShapesControl::CreateCylinder()
{
    auto cylinder = std::make_unique<CCylinder>(InputDensity(), InputHeight(), InputRadius());
    return cylinder;
}

std::unique_ptr<CParallelepiped> ShapesControl::CreateParallelepiped()
{
    auto parallelepiped = std::make_unique<CParallelepiped>(InputDensity(), InputWidth(), InputHeight(), InputDepth());
    return parallelepiped;
}

std::unique_ptr<CCompound> ShapesControl::CreateCompound()
{
    std::cout << "Enter the number of shapes in the compound shape: ";
    int numberOfShapes = 0;
    std::cin >> numberOfShapes;
    std::cout << std::endl;

    if (numberOfShapes <= 0)
    {
        throw std::invalid_argument("Enter at least one shape!\n");
    }

    auto compound = std::make_unique<CCompound>();

    auto addShapeFunc = [&](std::unique_ptr<CBody> child) -> bool
    {
        return compound->AddChildBody(std::move(child));
    };

    for (int i = 0; i < numberOfShapes; i++)
    {
        ShapeIdentifier(addShapeFunc);
    }

    return compound;
}

void ShapesControl::PrintShapesInfo() const
{
    if (m_shapes.size() == 0)
    {
        std::cout << "No shapes added!" << std::endl << std::endl;
        return;
    }

    for (auto& sh : m_shapes)
    {
        std::cout << sh->ToString() << std::endl;
    }
}

bool ShapesControl::AddShape(std::unique_ptr<CBody> shape)
{
    m_shapes.push_back(std::move(shape));
    return true;
}

int ShapesControl::SelectionOfShapesList() const
{
    std::cout << "Choose a shape:" << std::endl;
    std::cout << "1. Sphere" << std::endl;
    std::cout << "2. Cone" << std::endl;
    std::cout << "3. Cylinder" << std::endl;
    std::cout << "4. Parallelepiped" << std::endl;
    std::cout << "5. Compound shape" << std::endl;
    std::cout << "Enter the number corresponding to the shape: ";

    int choice = 0;
    std::cin >> choice;
    std::cout << std::endl;
    return choice;
}

bool ShapesControl::ShapeIdentifier(std::function<bool(std::unique_ptr<CBody>)> addShapeFunc)
{
    int choice = SelectionOfShapesList();
    switch (choice)
    {
    case 1:
        addShapeFunc(CreateSphere());
        std::cout << std::endl;
        std::cout << "Sphere added!" << std::endl << std::endl;
        break;
    case 2:
        addShapeFunc(CreateCone());
        std::cout << std::endl;
        std::cout << "Cone added!" << std::endl << std::endl;
        break;
    case 3:
        addShapeFunc(CreateCylinder());
        std::cout << std::endl;
        std::cout << "Cylinder added!" << std::endl << std::endl;
        break;
    case 4:
        addShapeFunc(CreateParallelepiped());
        std::cout << std::endl;
        std::cout << "Parallelepiped added!" << std::endl << std::endl;
        break;
    case 5:
        addShapeFunc(CreateCompound());
        std::cout << "Compound Shape added!" << std::endl << std::endl;
        break;
    default:
        std::cout << "Invalid choice!" << std::endl << std::endl;
        return false;
    }
    return true;
}

bool ShapesControl::InputHandler()
{
    std::cout << "Choose an action:" << std::endl;
    std::cout << "1. Add a shape." << std::endl;
    std::cout << "2. Show the body with the greatest mass." << std::endl;
    std::cout << "3. Show the body that is lightest in water." << std::endl;
    std::cout << "4. Print shapes information." << std::endl;
    std::cout << "Enter your choice: ";

    int choice;
    std::cin >> choice;
    std::cout << std::endl;

    auto addShapeFunc = [&](std::unique_ptr<CBody> shape) -> bool
    {
        return AddShape(std::move(shape));
    };

    switch (choice)
    {
    case 1:
        ShapeIdentifier(addShapeFunc);
        break;
    case 2:
        ShowHeaviestBody();
        break;
    case 3:
        ShowLightestBodyInTheWater();
        break;
    case 4:
        PrintShapesInfo();
        break;
    default:
        std::cout << "Invalid choice! Please enter a number between 1 and 4." << std::endl << std::endl;
        return false;
    }
    return true;
}