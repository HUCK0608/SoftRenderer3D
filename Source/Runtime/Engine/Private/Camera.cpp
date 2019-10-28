#include "Precompiled.h"
#include "Camera.h"

GameObject & Camera::GetGameObject()
{
	return gameObject;
}

Matrix4x4 Camera::GetViewMatrix(GameObject & LookAt)
{
	Vector3 viewZ = (LookAt.GetTransform().GetPosition() - gameObject.GetTransform().GetPosition()).Normalize();
	Vector3 viewX = Vector3::UnitY.Cross(viewZ).Normalize();
	if (viewX.IsZero())
		viewX = Vector3::UnitX;

	Vector3 viewY = viewX.Cross(viewZ).Normalize();

	return Matrix4x4();
}

void Camera::SetFOV(float InFOV)
{
	FOV = InFOV;
}

float Camera::GetFOV()
{
	return FOV;
}
