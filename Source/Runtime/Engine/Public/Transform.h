#pragma once

#include "Matrix4x4.h"

class Transform
{
public:
	Matrix4x4 GetTRS() const;

	void SetPosition(const Vector3& InPosition);
	Vector3 GetPosition() { return Position; }

	void SetRotation(const Vector3& InRotationDegree);
	void SetScale(const Vector3& InScale);

	void AddPosition(const Vector3& InPosition);
	void AddRotation(const Vector3& InRotationDegree);
	void AddScale(const Vector3& InScale);

private:
	Vector3 Position = Vector3::Zero;
	Vector3 RotationInDegree = Vector3::Zero;
	Vector3 Scale = Vector3::One;
};
