#include "Precompiled.h"
#include "Camera.h"

Transform & Camera::GetTransform ()
{
	return transform;
}

Matrix4x4 Camera::GetViewMatrix(GameObject & target)
{
	Vector3 viewZ = (transform.GetPosition() - target.GetTransform().GetPosition()).Normalize();
	Vector3 viewX = Vector3::UnitY.Cross(viewZ).Normalize();
	if (viewX.IsZero())
		viewX = Vector3::UnitX;

	Vector3 viewY = viewX.Cross(viewZ).Normalize();

	Matrix4x4 virMat = Matrix4x4(Vector4(viewX, false), Vector4(viewY, false), Vector4(viewZ, false), Vector4::UnitW).Tranpose();
	Matrix4x4 vitMat = Matrix4x4(Vector4::UnitX, Vector4::UnitY, Vector4::UnitZ, Vector4(-transform.GetPosition()));
	Matrix4x4 vMat = virMat * vitMat;

	return virMat * vitMat;
}
