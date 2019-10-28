#pragma once
#include "Transform.h"

class GameObject
{
public:
	GameObject() {}

	Transform& GetTransform();

private:
	Transform Transform;
};