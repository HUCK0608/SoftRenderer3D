#pragma once

class Transform
{
public:
	Transform() = default;

	Vector3 Right = Vector3::UnitX;
	Vector3 Up = Vector3::UnitY;
	Vector3 Forward = Vector3::UnitZ;

public:
	void SetPosition(const Vector3& InPosition);
	void AddPosition(const Vector3& InPosition);
	void SetRotation(const Rotator& InRotation);
	void AddYawRotation(float InDegree);
	void AddRollRotation(float InDegree);
	void AddPitchRotation(float InDegree);
	void SetScale(const Vector3& InScale);
	Matrix4x4 GetModelingMatrix() const;
	Vector3 GetPosition() const;
	void CalcLocalAxis();

private:
	Vector3 Position;
	Rotator Rotation;
	Vector3 Scale = Vector3::One;

	friend class GameObject;
	friend class Camera;
};

