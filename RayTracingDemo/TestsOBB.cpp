#include "catch.h"

#include <iostream>
#include <array>
#include <string>
#include <cmath>

#include "TestHelper.h"
#include "Ray.h"
#include "OBB.h"

struct OBBData
{
	Vector3D colour;
	Vector3D center;
	std::array<Vector3D, 3> uvw;
	std::array<double, 3> dimensions;
};

struct OBBTestData
{
	OBBData obbData;
	std::array<Vector3D, 2> rayData;
	bool hits;
	double distance;
};

SCENARIO("An OBB can be created and used for correct intersection testing with rays", "[Plane]")
{
	typedef Vector3D Vec3;
	// OBB: colour, center, u, v, w, width, height, depth
	// Ray: origin, direction'
	std::vector<OBBTestData> testData =
	{
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 9.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 2.5), {Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0), Vec3(1.0, 0.0, 0.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 11.5},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -3.45), {Vec3(0.0, 0.0, 1.0), Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 5.55},

		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 5.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 14.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.5, 0.5), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 9.5},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.0, 0.5), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 9.5},
		{{Vec3(0.0, 0.0, 0.0), Vec3(-0.5, -0.5, 0.5), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 9.5},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.5, -0.25, 0.5), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 9.5},

		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {7, 7, 7}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 3.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 2.5), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {3, 2, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 11.5},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1.23, 4.56, 7.89}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 2.11},

		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.5, 0.5, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 9.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(-0.5, 0.5, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 9.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.5, -0.5, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 9.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(-0.5, -0.5, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 9.0},


		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 9.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 2.5, 0.0), {Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0), Vec3(1.0, 0.0, 0.0)}, {1, 1, 1}},
		{Vec3(0.0, -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 11.5},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, -3.45, 0.0), {Vec3(0.0, 0.0, 1.0), Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0)}, {1, 1, 1}},
		{Vec3(0.0, -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 5.55},

		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 5.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 14.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.5, 0.5), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 9.5},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.5, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 9.5},
		{{Vec3(0.0, 0.0, 0.0), Vec3(-0.5, 0.5, -0.5), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 9.5},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.5, -0.25), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 9.5},

		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {7, 7, 7}},
		{Vec3(0.0, -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 3.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 2.5, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {3, 2, 1}},
		{Vec3(0.0, -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 10.5},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1.23, 4.56, 7.89}},
		{Vec3(0.0, -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 5.44},

		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.5, -10.0, 0.5), Vec3(0.0, 1.0, 0.0)}, true, 9.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(-0.5, -10.0, 0.5), Vec3(0.0, 1.0, 0.0)}, true, 9.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.5, -10.0, -0.5), Vec3(0.0, 1.0, 0.0)}, true, 9.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(-0.5, -10.0, -0.5), Vec3(0.0, 1.0, 0.0)}, true, 9.0},

		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, sqrt(0.5))}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10 - sqrt(2)},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(-sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5))}, {1, 1, 1}},
		{Vec3(sqrt(2) / 2, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10 - sqrt(2) / 2},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(-sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5))}, {1, 1, 1}},
		{Vec3(-sqrt(2) / 2, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10 - sqrt(2) / 2},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(-sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5))}, {1, 1, 1}},
		{Vec3(sqrt(2) / 2, 0.5, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10 - sqrt(2) / 2},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(-sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5))}, {1, 1, 1}},
		{Vec3(-sqrt(2) / 2, 0.5, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10 - sqrt(2) / 2},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(-sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5))}, {1, 1, 1}},
		{Vec3(sqrt(2) / 2, -0.5, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10 - sqrt(2) / 2},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(-sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5))}, {1, 1, 1}},
		{Vec3(-sqrt(2) / 2, -0.5, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10 - sqrt(2) / 2},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, sqrt(0.5))}, {1, 3.4, 2}},
		{Vec3(0.0, -0.2, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10 - sqrt(2)},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, sqrt(0.5))}, {1, 3.7, 2}},
		{Vec3(sqrt(0.5), 0.1, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10 - 2.121320},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -2.0), Vec3(sqrt(0.5), 0.0, sqrt(0.5))}, true, sqrt(2)},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -2.0), Vec3(-sqrt(0.5), 0.0, sqrt(0.5))}, true, sqrt(2)},


		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 2.5), {Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0), Vec3(1.0, 0.0, 0.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -3.45), {Vec3(0.0, 0.0, 1.0), Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},

		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 5.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.5, 0.5), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.0, 0.5), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(-0.5, -0.5, 0.5), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.5, -0.25, 0.5), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},

		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {7, 7, 7}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 2.5), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {3, 2, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1.23, 4.56, 7.89}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},

		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.5, 0.5, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(-0.5, 0.5, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.5, -0.5, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(-0.5, -0.5, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},

		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, sqrt(0.5))}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(-sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5))}, {1, 1, 1}},
		{Vec3(sqrt(2) / 2, 0.0, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(-sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5))}, {1, 1, 1}},
		{Vec3(-sqrt(2) / 2, 0.0, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(-sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5))}, {1, 1, 1}},
		{Vec3(sqrt(2) / 2, 0.5, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(-sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5))}, {1, 1, 1}},
		{Vec3(-sqrt(2) / 2, 0.5, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(-sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5))}, {1, 1, 1}},
		{Vec3(sqrt(2) / 2, -0.5, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(-sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5))}, {1, 1, 1}},
		{Vec3(-sqrt(2) / 2, -0.5, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, sqrt(0.5))}, {1, 3.4, 2}},
		{Vec3(0.0, -0.2, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(sqrt(0.5), 0.0, sqrt(0.5)), Vec3(0.0, 1.0, 0.0), Vec3(-sqrt(0.5), 0.0, sqrt(0.5))}, {1, 3.7, 2}},
		{Vec3(sqrt(0.5), 0.1, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -2.0), Vec3(sqrt(0.5), 0.0, -sqrt(0.5))}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 0.0, -2.0), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5))}, false, 0.0},

		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(1.1, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(-1.1, 0.0, 10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, -10.0, 1.1), Vec3(0.0, 1.0, 0.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 10.0, -1.1), Vec3(0.0, -1.0, 0.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(-10.0, 1.1, 0.0), Vec3(1.0, 0.0, 0.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(10.0, -1.1, 0.0), Vec3(-1.0, 0.0, 0.0)}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {0.95, 0.9, 0.85}},
		{Vec3(0.0, 0.0, -2.1), Vec3(sqrt(0.5), 0.0, sqrt(0.5))}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1.1, 1.2, 1.3}},
		{Vec3(0.0, 0.0, -4.2), Vec3(-sqrt(0.5), 0.0, sqrt(0.5))}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(-1.1, -0.1, 0.2), Vec3(-sqrt(0.5), 0.0, sqrt(0.5))}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(-0.25, 0.5, 1.1), Vec3(-sqrt(0.5), 0.0, sqrt(0.5))}, false, 0.0},
		{{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), {Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)}, {1, 1, 1}},
		{Vec3(0.0, 1.1, 0.0), Vec3(-sqrt(0.5), 0.0, sqrt(0.5))}, false, 0.0},
	};

	WHEN("An OBB object is created and intersection tests are performed with rays")
	{
		THEN("The intersection function should correctly indicate if the ray hits the plane, and if hits, at what distance")
		{
			for (auto& input : testData)
			{
				auto& obbData = input.obbData;
				auto& rayData = input.rayData;
				OBB obb(obbData.colour, obbData.center, obbData.uvw[0], obbData.uvw[1], obbData.uvw[2],
					obbData.dimensions[0], obbData.dimensions[1], obbData.dimensions[2]);
				Ray ray(rayData[0], rayData[1]);
				bool resultingHit = false;
				double resultingDistance = 0.0;
				resultingHit = obb.Intersection(ray, resultingDistance);

				//FORTS�TT H�R
				std::string info = "OBB: center(" + ToString(obbData.center) + "), u vector(" + ToString(obbData.uvw[0])
					+ "), v vector(" + ToString(obbData.uvw[1]) + "), w vector(" + ToString(obbData.uvw[2])
					+ "), width = " + std::to_string(obbData.dimensions[0]) + "), height = " + std::to_string(obbData.dimensions[1])
					+ "), depth = " + std::to_string(obbData.dimensions[2]);
				info += "\nRay: origin(" + ToString(rayData[0]) + "), direction(" + ToString(rayData[1]) + ")";
				info += "\nExpected to hit: " + std::string(input.hits == true ? "yes" : "no");
				info += input.hits == true ? ("\nExpected distance to hit: " + std::to_string(input.distance)) : "";
				info += "\nResulted in hit: " + std::string(resultingHit == true ? "yes" : "no");
				info += resultingHit == true ? ("\nResulting distance to hit: " + std::to_string(resultingDistance)) : "";

				INFO(info);
				REQUIRE(resultingHit == input.hits);
				if (input.hits)
					REQUIRE(ApproximatelyEqual(resultingDistance, input.distance));

			}
		}
	}
}