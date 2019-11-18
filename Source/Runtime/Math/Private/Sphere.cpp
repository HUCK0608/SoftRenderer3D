#include "Precompiled.h"
#include "Sphere.h"

void Sphere::CalcBoundingBox(Vector4 * InVertices, int VertexCount)
{
	Vector4 avPos;
	for (int vi = 0; vi < VertexCount; vi++)
		avPos += InVertices[vi];

	avPos /= VertexCount;
	Center = avPos.ToVector3();

	float maxSize = 0.f;
	for (int vi = 0; vi < VertexCount; vi++)
	{
		float sizeSquared = (avPos - InVertices[vi]).SizeSquared();

		if (sizeSquared > maxSize)
			maxSize = sizeSquared;
	}

	Radius = sqrtf(maxSize);
}
