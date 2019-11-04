
#include "Precompiled.h"
#include "SoftRendererImpl3D.h"
#include "SoftRenderer.h"

SoftRendererImpl3D::SoftRendererImpl3D(SoftRenderer* InOwner)
{
	RSI = InOwner->RSI.get();
	ScreenSize = InOwner->CurrentScreenSize;
	InputManager = InOwner->GetInputManager();
}

SoftRendererImpl3D::~SoftRendererImpl3D()
{
}


void SoftRendererImpl3D::RenderFrameImpl()
{
	assert(RSI != nullptr && RSI->IsInitialized() && !ScreenSize.HasZero());

	const int vertexCount = 24;
	static Vector4 v[vertexCount] = {
		// Front 
		Vector4(0.5f, -0.5f, 0.5f),
		Vector4(0.5f, 0.5f, 0.5f),
		Vector4(0.5f, 0.5f, -0.5f),
		Vector4(0.5f, -0.5f, -0.5f),
		// Left
		Vector4(-0.5f, -0.5f, 0.5f),
		Vector4(-0.5f, 0.5f, 0.5f),
		Vector4(0.5f, 0.5f, 0.5f),
		Vector4(0.5f, -0.5f, 0.5f),
		// Right
		Vector4(0.5f, -0.5f, -0.5f),
		Vector4(0.5f, 0.5f, -0.5f),
		Vector4(-0.5f, 0.5f, -0.5f),
		Vector4(-0.5f, -0.5f, -0.5f),
		// Back
		Vector4(-0.5f, -0.5f, -0.5f),
		Vector4(-0.5f, 0.5f, -0.5f),
		Vector4(-0.5f, 0.5f, 0.5f),
		Vector4(-0.5f, -0.5f, 0.5f),
		// Top
		Vector4(0.5f, 0.5f, 0.5f),
		Vector4(-0.5f, 0.5f, 0.5f),
		Vector4(-0.5f, 0.5f, -0.5f),
		Vector4(0.5f, 0.5f, -0.5f),
		// Bottom
		Vector4(-0.5f, -0.5f, 0.5f),
		Vector4(0.5f, -0.5f, 0.5f),
		Vector4(0.5f, -0.5f, -0.5f),
		Vector4(-0.5f, -0.5f, -0.5f)
	};

	const int triangleCount = 12;
	const int indexCount = triangleCount * 3;
	int i[indexCount] = {
	 0, 2, 1, 0, 3, 2,
	 4, 6, 5, 4, 7, 6,
	 8, 10, 9, 8, 11, 10,
	 12, 14, 13, 12, 15, 14,
	 16, 18, 17, 16, 19, 18,
	 20, 22, 21, 20, 23, 22
	};
	
	static float a = (float)ScreenSize.X / (float)ScreenSize.Y;
	static float repA = (float)ScreenSize.Y / (float)ScreenSize.X;
	static float d = 1.f / tanf(Math::Deg2Rad(FOV) * 0.5f);

	for (int t = 0; t < triangleCount; t++)
	{
		Vector4 tp[3];
		tp[0] = v[i[t * 3]];
		tp[1] = v[i[t * 3 + 1]];
		tp[2] = v[i[t * 3 + 2]];

		for (int ti = 0; ti < 3; ti++)
		{
			tp[ti] = FinalMatrix * tp[ti];

			float repZ = 1.f / -tp[ti].Z;
			tp[ti].Y = tp[ti].Y * d * repZ;
			tp[ti].X = tp[ti].X * d * repZ * repA;

			tp[ti].X *= (ScreenSize.X * 0.5f);
			tp[ti].Y *= (ScreenSize.Y * 0.5f);
		}

		RSI->DrawLine(tp[0].ToVector2(), tp[1].ToVector2(), LinearColor::Red);
		RSI->DrawLine(tp[0].ToVector2(), tp[2].ToVector2(), LinearColor::Red);
		RSI->DrawLine(tp[1].ToVector2(), tp[2].ToVector2(), LinearColor::Red);
	}
}

void SoftRendererImpl3D::UpdateImpl(float DeltaSeconds)
{
	// 모델링 변환 행렬
	static GameObject quad;
	quad.GetTransform().SetScale(Vector3::One * 100.f);

	static float moveSpeed = 500.f;
	static float rotationSpeed = 180.f;

	quad.GetTransform().AddPosition(Vector3::UnitZ * (InputManager.GetYAxis() * moveSpeed * DeltaSeconds));
	quad.GetTransform().AddRotation(Vector3::UnitY * (InputManager.GetXAxis() * rotationSpeed * DeltaSeconds));

	Matrix4x4 TRSMat = quad.GetTransform().GetTRS();

	Camera camera;
	camera.GetGameObject().GetTransform().SetPosition(Vector3(0.f, 500.f, -500.f));
	FinalMatrix = camera.GetViewMatrix(quad) * TRSMat;
}
