#pragma once
#include "Vector3.h"

struct Plane
{
	Plane() = default;
	Plane(const Vector3& InNormal, const float InD) : Normal(InNormal), D(InD) {}
	Plane(const Vector3& InP1, const Vector3& InP2, const Vector3& InP3);

	Vector3 Normal = Vector3::UnitY;
	float D = 0.f;
};