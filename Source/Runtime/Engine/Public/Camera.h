#pragma once
#include "GameObject.h"

class Camera
{
public:
	Camera() {}

	GameObject& GetGameObject();

	Matrix4x4 GetViewMatrix(GameObject& LookAt);

	void SetFOV(float InFOV);
	float GetFOV();

private:
	GameObject gameObject;
	float FOV = 60.f;
};