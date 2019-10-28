#include "Precompiled.h"
#include "Transform.h"

Matrix4x4 Transform::GetTRS() const
{
	Matrix4x4 tMat = Matrix4x4(Vector4::UnitX, Vector4::UnitY, Vector4::UnitZ, Vector4(Position.X, Position.Y, Position.Z, 1.f));

	float radPitch, radYaw, radRoll;
	radPitch = Math::Deg2Rad(RotationInDegree.X);
	radYaw = Math::Deg2Rad(RotationInDegree.Y);
	radRoll = Math::Deg2Rad(RotationInDegree.Z);

	float sp = sinf(radPitch);
	float cp = cosf(radPitch);
	float sr = sinf(radRoll);
	float cr = cosf(radRoll);
	float sy = sinf(radYaw);
	float cy = cosf(radYaw);

	Matrix4x4 rMat = Matrix4x4(Vector4(cr * cy + sr * sp * sy, sr * cy - cr * sp * sy, -cp * sy, 0.f),
							   Vector4(-sr * cp, cr * cp, -sp, 0.f),
							   Vector4(cr * sy - sr * sp * cy, sr * sy + cr * sp * cy, cp * cy, 0.f),
							   Vector4::UnitW);

	Matrix4x4 sMat = Matrix4x4(Vector4::UnitX * Scale.X, Vector4::UnitY * Scale.Y, Vector4::UnitY * Scale.Z, Vector4::UnitW);

	return tMat * rMat * sMat;
}

void Transform::SetPosition(const Vector3 & InPosition)
{
	Position = InPosition;
}

void Transform::SetRotation(const Vector3 & InRotationDegree)
{
	RotationInDegree = InRotationDegree;
}

void Transform::SetScale(const Vector3 & InScale)
{
	Scale = InScale;
}

void Transform::AddPosition(const Vector3 & InPosition)
{
	Position += InPosition;
}

void Transform::AddRotation(const Vector3 & InRotationDegree)
{
	RotationInDegree += InRotationDegree;
}

void Transform::AddScale(const Vector3 & InScale)
{
	Scale += InScale;
}
