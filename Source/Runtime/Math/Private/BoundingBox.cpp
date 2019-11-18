#include "Precompiled.h"
#include "BoundingBox.h"

void BoundingBox::CalcBoundingBox(Vector4 * InVertices, int VertexCount)
{
	Vector3 max = Vector3::InfinityNeg;
	Vector3 min = Vector3::Infinity;
	Vector4 avPos = Vector4::Zero;

	for (int vi = 0; vi < VertexCount; vi++)
	{
		avPos += InVertices[vi];

		if (max.X < InVertices[vi].X)
			max.X = InVertices[vi].X;
		else if (min.X > InVertices[vi].X)
			min.X = InVertices[vi].X;

		if (max.Y < InVertices[vi].Y)
			max.Y = InVertices[vi].Y;
		else if (min.Y > InVertices[vi].Y)
			min.Y = InVertices[vi].Y;

		if (max.Z < InVertices[vi].Z)
			max.Z = InVertices[vi].Z;
		else if (min.Z > InVertices[vi].Z)
			min.Z = InVertices[vi].Z;
	}

	avPos /= VertexCount;
	Center = avPos.ToVector3();

	Extent = Vector3((max.X - min.X) * 0.5f, (max.Y - min.Y) * 0.5f, (max.Z - min.Z) * 0.5f);
}
