#pragma once
#include "Vector4.h"

struct Sphere
{
	Sphere() = default;
	void CalcBoundingBox(Vector4* InVertices, int VertexCount);

	Vector3 Center = Vector3::Zero;
	float Radius = 0.f;
};