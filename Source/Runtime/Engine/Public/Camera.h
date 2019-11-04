#pragma once
#include "GameObject.h"

class Camera
{
public:
	Camera() {}

	GameObject& GetGameObject();

	Matrix4x4 GetViewMatrix(GameObject& LookAt);

private:
	GameObject gameObject;
};