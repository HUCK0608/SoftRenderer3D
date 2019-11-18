#pragma once
#include "Vector4.h"

struct BoundingBox
{
	BoundingBox() = default;
	void CalcBoundingBox(Vector4* InVertices, int VertexCount);

	Vector3 Center;
	Vector3 Extent;

};