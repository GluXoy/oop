#define CATCH_CONFIG_MAIN
#define _USE_MATH_DEFINES
#include "../../../catch2/catch.hpp"
#include "../Shapes/CBody.h"
#include "../Shapes/CSphere.h"
#include "../Shapes/CCone.h"
#include "../Shapes/CParallelepiped.h"
#include "../Shapes/CCylinder.h"
#include "../Shapes/CCompound.h"
#include <cmath>
#include <vector>
#include <memory>

TEST_CASE("Check Shapes Constructors")
{
	SECTION("CSphere constructor should initialized fields")
	{
		double density = 1000;
		double radius = 1;
		CSphere sphere(density, radius);
		CHECK(sphere.GetDensity() == density);
		CHECK(sphere.GetRadius() == radius);
	}

	SECTION("CCone constructor should initialized fields")
	{
		double density = 1000;
		double height = 1;
		double radius = 1;
		CCone cone(density, height, radius);
		CHECK(cone.GetDensity() == density);
		CHECK(cone.GetHeight() == height);
		CHECK(cone.GetBaseRadius() == radius);
	}

	SECTION("CCylinder constructor should initialized fields")
	{
		double density = 1000;
		double height = 1;
		double radius = 1;
		CCylinder cylinder(density, height, radius);
		CHECK(cylinder.GetDensity() == density);
		CHECK(cylinder.GetHeight() == height);
		CHECK(cylinder.GetBaseRadius() == radius);
	}

	SECTION("CParallelepiped constructor should initialized fields")
	{
		double density = 1000;
		double height = 1;
		double width = 1;
		double depth = 1;
		CParallelepiped parallelepiped(density, width, height, depth);
		CHECK(parallelepiped.GetDensity() == density);
		CHECK(parallelepiped.GetHeight() == height);
		CHECK(parallelepiped.GetWidth() == width);
		CHECK(parallelepiped.GetDepth() == depth);
	}
}

TEST_CASE("Manipulate with public fields")
{
	SECTION("CSphere")
	{
		SECTION("CSphere with initialized private fields should return correct volume")
		{
			double density = 1000;
			double radius = 1;
			CSphere sphere(density, radius);
			CHECK(sphere.GetVolume() == (pow(radius, 3) * M_PI) * 4 / 3);
		}

		SECTION("CSphere with initialized private fields should return correct mass")
		{
			double density = 1000;
			double radius = 1;
			CSphere sphere(density, radius);
			CHECK(sphere.GetMass() == sphere.GetVolume() * density);
		}
	}

	SECTION("CCone")
	{
		SECTION("CCone with initialized private fields should return correct volume")
		{
			double density = 1000;
			double height = 1;
			double radius = 1;
			CCone cone(density, height, radius);
			CHECK(cone.GetVolume() == (pow(radius, 2) * M_PI) * height * 1 / 3);
		}

		SECTION("CCone with initialized private fields should return correct mass")
		{
			double density = 1000;
			double height = 1;
			double radius = 1;
			CCone cone(density, height, radius);
			CHECK(cone.GetMass() == cone.GetVolume() * density);
		}
	}

	SECTION("CCylinder")
	{
		SECTION("CCylinder with initialized private fields should return correct volume")
		{
			double density = 1000;
			double height = 1;
			double radius = 1;
			CCylinder cylinder(density, height, radius);
			CHECK(cylinder.GetVolume() == (pow(radius, 2) * M_PI) * height);
		}

		SECTION("CCylinder with initialized private fields should return correct mass")
		{
			double density = 1000;
			double height = 1;
			double radius = 1;
			CCylinder cylinder(density, height, radius);
			CHECK(cylinder.GetMass() == cylinder.GetVolume() * density);
		}
	}

	SECTION("CParallelepiped")
	{
		SECTION("CParallelepiped with initialized private fields should return correct volume")
		{
			double density = 1000;
			double height = 1;
			double width = 1;
			double depth = 1;
			CParallelepiped parallelepiped(density, width, height, depth);
			CHECK(parallelepiped.GetVolume() == height * width * depth);
		}

		SECTION("CParallelepiped with initialized private fields should return correct mass")
		{
			double density = 1000;
			double height = 1;
			double width = 1;
			double depth = 1;
			CParallelepiped parallelepiped(density, width, height, depth);
			CHECK(parallelepiped.GetMass() == parallelepiped.GetVolume() * density);
		}
	}
}

TEST_CASE("Check CCompound")
{
	SECTION("...")
	{
		auto sphere = std::make_unique<CSphere>(1000, 1);
		auto cone = std::make_unique<CCone>(1000, 1, 1);
		auto cylinder = std::make_unique<CCylinder>(1000, 1, 1);
		auto plpd = std::make_unique<CParallelepiped>(1000, 1, 1, 1);

		auto compBody = std::make_unique<CCompound>();
		compBody->AddChildBody(std::move(sphere));
		compBody->AddChildBody(std::move(cone));

		CCompound compBody2;
		compBody2.AddChildBody(std::move(compBody));

		//std::cout << compBody->m_childs[0]->ToString() << std::endl;
		//std::cout << compBody->m_childs[1]->ToString() << std::endl;

		std::cout << compBody2.m_childs[0]->ToString() << std::endl;
		std::cout << compBody2.m_childs[0]->ToString() << std::endl;
	}
}