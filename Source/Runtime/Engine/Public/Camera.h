#pragma once
#include "GameObject.h"

class Camera
{
public:
	Camera() {}

	Transform& GetTransform();

	Matrix4x4 GetViewMatrix(GameObject& LookAt);

private:
	Transform transform;
};