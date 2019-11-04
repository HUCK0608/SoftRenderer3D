#pragma once
#include "Transform.h"
#include "Mesh.h"

class GameObject
{
public:
	GameObject() {}
	GameObject(Mesh& InMesh) : Mesh(InMesh) {}

	Transform& GetTransform();
	Mesh& GetMesh();

private:
	Transform Transform;
	Mesh Mesh;
};