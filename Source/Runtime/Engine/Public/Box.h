#pragma once
#include "Mesh.h"

class Box : public Mesh
{
public:
	Box() {
		Vector4 vertexes[24] = {
			// Front 
			Vector4(1.0f, -1.0f, 1.0f),
			Vector4(1.0f, 1.0f, 1.0f),
			Vector4(1.0f, 1.0f, -1.0f),
			Vector4(1.0f, -1.0f, -1.0f),
			// Left
			Vector4(-1.0f, -1.0f, 1.0f),
			Vector4(-1.0f, 1.0f, 1.0f),
			Vector4(1.0f, 1.0f, 1.0f),
			Vector4(1.0f, -1.0f, 1.0f),
			// Right
			Vector4(1.0f, -1.0f, -1.0f),
			Vector4(1.0f, 1.0f, -1.0f),
			Vector4(-1.0f, 1.0f, -1.0f),
			Vector4(-1.0f, -1.0f, -1.0f),
			// Back
			Vector4(-1.0f, -1.0f, -1.0f),
			Vector4(-1.0f, 1.0f, -1.0f),
			Vector4(-1.0f, 1.0f, 1.0f),
			Vector4(-1.0f, -1.0f, 1.0f),
			// Top
			Vector4(1.0f, 1.0f, 1.0f),
			Vector4(-1.0f, 1.0f, 1.0f),
			Vector4(-1.0f, 1.0f, -1.0f),
			Vector4(1.0f, 1.0f, -1.0f),
			// Bottom
			Vector4(-1.0f, -1.0f, 1.0f),
			Vector4(1.0f, -1.0f, 1.0f),
			Vector4(1.0f, -1.0f, -1.0f),
			Vector4(-1.0f, -1.0f, -1.0f)
		};

		int indices[36] = {
		0, 2, 1, 0, 3, 2,
		4, 6, 5, 4, 7, 6,
		8, 10, 9, 8, 11, 10,
		12, 14, 13, 12, 15, 14,
		16, 18, 17, 16, 19, 18,
		20, 22, 21, 20, 23, 22
		};

		SetVertexes(vertexes);
		SetIndices(indices);
	}
};