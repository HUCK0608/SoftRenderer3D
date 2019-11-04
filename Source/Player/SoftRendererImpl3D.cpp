
#include "Precompiled.h"
#include "SoftRendererImpl3D.h"
#include "SoftRenderer.h"

SoftRendererImpl3D::SoftRendererImpl3D(SoftRenderer* InOwner)
{
	RSI = InOwner->RSI.get();
	ScreenSize = InOwner->CurrentScreenSize;
	InputManager = InOwner->GetInputManager();

	const int gameObjectCount = 2;
	GameObject box = GameObject(Box());
	box.GetTransform().SetScale(Vector3::One * 100.f);
	GameObject box2 = GameObject(Box());
	box2.GetTransform().SetScale(Vector3::One * 50.0f);
	box2.GetTransform().SetPosition(Vector3(150.f, 0.f, 0.f));

	GameObject gameObjects[gameObjectCount] = {
		box,
		box2
	};

	GameObjects = gameObjects;
	GameObjectCount = gameObjectCount;
}

SoftRendererImpl3D::~SoftRendererImpl3D()
{
}


void SoftRendererImpl3D::RenderFrameImpl()
{
	assert(RSI != nullptr && RSI->IsInitialized() && !ScreenSize.HasZero());

	for (int i = 0; i < GameObjectCount; i++)
	{
		int triangleCount = GameObjects[i].GetMesh().GetIndexCount / 3;

		for (int t = 0; t < triangleCount; t++)
		{
			Vector4 tp[3];
			tp[0] = v[i[t * 3]];
			tp[1] = v[i[t * 3 + 1]];
			tp[2] = v[i[t * 3 + 2]];

			// 최종행렬 적용
			for (int ti = 0; ti < 3; ti++)
			{
				tp[ti] = FinalMatrix * tp[ti];
				float repW = 1.f / tp[ti].W;
				tp[ti].X *= repW;
				tp[ti].Y *= repW;
				tp[ti].Z *= repW;
			}

			// Backface Culling
			Vector3 edge1 = (tp[1] - tp[0]).ToVector3();
			Vector3 edge2 = (tp[2] - tp[0]).ToVector3();
			Vector3 faceNormal = edge1.Cross(edge2).Normalize();
			static Vector3 cameraDir = -Vector3::UnitZ;

			if (cameraDir.Dot(faceNormal) < 0.f)
				continue;

			for (int ti = 0; ti < 3; ti++)
			{
				tp[ti].X *= (ScreenSize.X * 0.5f);
				tp[ti].Y *= (ScreenSize.Y * 0.5f);
			}

			RSI->DrawLine(tp[0].ToVector2(), tp[1].ToVector2(), LinearColor::Red);
			RSI->DrawLine(tp[0].ToVector2(), tp[2].ToVector2(), LinearColor::Red);
			RSI->DrawLine(tp[1].ToVector2(), tp[2].ToVector2(), LinearColor::Red);
		}
	}
}

void SoftRendererImpl3D::UpdateImpl(float DeltaSeconds)
{
	// 모델링 변환 행렬
	static GameObject box = GameObject(Box());
	box.GetTransform().SetScale(Vector3::One * 100.f);

	static float moveSpeed = 500.f;
	static float rotationSpeed = 180.f;

	box.GetTransform().AddPosition(Vector3::UnitZ * (InputManager.GetYAxis() * moveSpeed * DeltaSeconds));
	box.GetTransform().AddRotation(Vector3::UnitY * (InputManager.GetXAxis() * rotationSpeed * DeltaSeconds));

	Matrix4x4 TRSMat = box.GetTransform().GetTRS();

	// 투영 행렬
	static float repA = (float)ScreenSize.Y / (float)ScreenSize.X;
	static float d = 1.f / tanf(Math::Deg2Rad(FOV) * 0.5f);
	static float n = 5.5f;
	static float f = 100.0f;
	float repNF = 1.f / (n - f);
	float k = f / repNF;
	float l = f * n / repNF;
	Matrix4x4 pMat(Vector4::UnitX * repA * d, 
				   Vector4::UnitY * d, 
				   Vector4(0.f, 0.f, k, -1.f), 
				   Vector4(0.f, 0.f, l, 0.f));

	Camera camera;
	camera.GetTransform().SetPosition(Vector3(0.f, 500.f, -500.f));
	FinalMatrix = pMat * camera.GetViewMatrix(box) * TRSMat;
}
