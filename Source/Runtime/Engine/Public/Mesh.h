#pragma once
#include "Vector4.h"

class Mesh
{
public:
	Mesh() {}
	Mesh(Vector4* InVertexes, int* InIndices) { SetVertexes(InVertexes); SetIndices(InIndices); }

	void SetVertexes(Vector4* InVertexes) { Vertexes = InVertexes; VertexCount = sizeof(Vertexes) / sizeof(Vector4); }
	void SetIndices(int* InIndices) { Indices = InIndices; IndexCount = sizeof(Indices) / sizeof(int); }

	Vector4* GetVertexes() { return Vertexes; }
	int* GetIndices() { return Indices; }
	int GetVertexCount() { return VertexCount; }
	int GetIndexCount() { return IndexCount; }

private:
	Vector4* Vertexes;
	int* Indices;
	int VertexCount = 0;
	int IndexCount = 0;
};
