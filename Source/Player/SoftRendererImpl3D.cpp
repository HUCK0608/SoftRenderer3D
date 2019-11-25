
#include "Precompiled.h"
#include "SoftRendererImpl3D.h"
#include "SoftRenderer.h"

SoftRendererImpl3D::SoftRendererImpl3D(SoftRenderer* InOwner)
{
	RSI = InOwner->RSI.get();
	ScreenSize = InOwner->CurrentScreenSize;
	InputManager = InOwner->GetInputManager();

	LoadResource();
	LoadScene();
}

SoftRendererImpl3D::~SoftRendererImpl3D()
{
	//for (auto& g : Scene)
	//{
	//	g.GetMesh().ReleaseAllBuffers();
	//}
}

void SoftRendererImpl3D::LoadResource()
{
	// Load Mesh Resource
	const int vertexCount = 24;
	const int triangleCount = 12;
	const int indexCount = triangleCount * 3;

	Vector4* v = new Vector4[vertexCount] {
		// Right 
		Vector4(0.5f, -0.5f, 0.5f),
		Vector4(0.5f, 0.5f, 0.5f),
		Vector4(0.5f, 0.5f, -0.5f),
		Vector4(0.5f, -0.5f, -0.5f),
		// Front
		Vector4(-0.5f, -0.5f, 0.5f),
		Vector4(-0.5f, 0.5f, 0.5f),
		Vector4(0.5f, 0.5f, 0.5f),
		Vector4(0.5f, -0.5f, 0.5f),
		// Back
		Vector4(0.5f, -0.5f, -0.5f),
		Vector4(0.5f, 0.5f, -0.5f),
		Vector4(-0.5f, 0.5f, -0.5f),
		Vector4(-0.5f, -0.5f, -0.5f),
		// Left
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

	Color32* c = new Color32[vertexCount] {
		// Right
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		// Front
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		// Back
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		// Left
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		// Top
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		// Bottom
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		Color32(0, 0, 0),
		Color32(0, 0, 0)
	};

	int* i = new int[indexCount] {
	 0, 2, 1, 0, 3, 2,
	 4, 6, 5, 4, 7, 6,
	 8, 10, 9, 8, 11, 10,
	 12, 14, 13, 12, 15, 14,
	 16, 18, 17, 16, 19, 18,
	 20, 22, 21, 20, 23, 22
	};

	SharedCubeMesh = std::make_unique<Mesh>();
	SharedCubeMesh.get()->SetMesh(vertexCount, indexCount, v, i);
	SharedCubeMesh.get()->SetColor(c);

	delete[] v;
	delete[] i;
}

void SoftRendererImpl3D::LoadScene()
{
	// Setup Game Scene 
	GameObject* player = new GameObject();
	player->SetMesh(SharedCubeMesh.get());
	player->GetTransform().SetPosition(Vector3::Zero);
	player->GetTransform().SetRotation(Rotator(0.f, 0.f, 0.f));
	player->GetTransform().SetScale(Vector3::One * 100.f);
	Scene.emplace_back(player);

	for (int i = 0; i < 5; ++i)
	{
		GameObject* worldStatic = new GameObject();
		worldStatic->SetMesh(SharedCubeMesh.get());
		worldStatic->GetTransform().SetPosition(Vector3(0.f, 0.f, i * 100.f));
		worldStatic->GetTransform().SetScale(Vector3::One * 100.f);

		Scene.emplace_back(worldStatic);
	}

	Camera.GetTransform().SetPosition(Vector3(500.f, 500.f, -500.f));
}

void SoftRendererImpl3D::RenderFrameImpl()
{
	assert(RSI != nullptr && RSI->IsInitialized() && !ScreenSize.HasZero());

	auto player = Scene[0].get();
	Matrix4x4 vMat = Camera.GetLookAtMatrix(*player);
	Matrix4x4 pMat = Camera.GetPerspectiveMatrix(ScreenSize.X, ScreenSize.Y);

	for (auto& g : Scene)
	{
		Matrix4x4 mMat = g->GetTransform().GetModelingMatrix();

		Matrix4x4 m[3] = { mMat, vMat, pMat };

		// Frustum 평면 구하기
		// Near, Far
		Plane nearPlane = Plane(Vector3::UnitZ, -Camera.GetNearZ());
		Plane farPlane = Plane(-Vector3::UnitZ, -Camera.GetFarZ());
		
		Mesh* meshToRender = player->GetMesh();
		int vertexCount = meshToRender->GetVertexCount();
		int indexCount = meshToRender->GetIndexCount();
		Vector4* meshVertexBuffer = meshToRender->GetVertexBuffer();
		Color32* meshColorBuffer = meshToRender->GetColorBuffer();
		int* i = meshToRender->GetIndexBuffer();
		VertexData* v = new VertexData[vertexCount];
		for (int vi = 0; vi < vertexCount; ++vi)
		{
			v[vi].Position = meshVertexBuffer[vi];
			v[vi].Color = LinearColor(meshColorBuffer[vi]);
		}

		RSI->SetUniformMatrix(m);
		RSI->SetVertexBuffer(v);
		RSI->SetIndexBuffer(i);
		RSI->DrawTrianglePrimitive(vertexCount, indexCount);

		delete[] v;
	}

	DrawGizmo3D(vMat, pMat);
	DrawXYPlane(vMat, pMat);
}

void SoftRendererImpl3D::UpdateImpl(float DeltaSeconds)
{
	// 게임 로직.
	static float moveSpeed = 1000.f;
	static float rotateSpeed = 180.f;

	auto player = Scene[0].get();
	Vector3 deltaPos = Vector3::UnitZ * InputManager.GetYAxis() * moveSpeed * DeltaSeconds;
	float deltaDegree = InputManager.GetXAxis() * rotateSpeed * DeltaSeconds;
	float deltaDegree2 = InputManager.GetYAxis() * rotateSpeed * DeltaSeconds;
	player->GetTransform().AddPosition(deltaPos);
	player->GetTransform().AddYawRotation(deltaDegree);
}

void SoftRendererImpl3D::DrawGizmo3D(Matrix4x4 InVMatrix, Matrix4x4 InPMatrix)
{
	const int gizmosVertexCount = 6;
	VertexData v[gizmosVertexCount] = {
		VertexData(Vector3::Zero, LinearColor::Red),
		VertexData(Vector3::UnitX * 500.f, LinearColor::Red),
		VertexData(Vector3::Zero, LinearColor::Green),
		VertexData(Vector3::UnitY * 500.f, LinearColor::Green),
		VertexData(Vector3::Zero, LinearColor::Blue),
		VertexData(Vector3::UnitZ * 500.f, LinearColor::Blue),
	};

	const int gizmosLineCount = 3;
	const int gizmosIndexCount = gizmosLineCount * 2;
	int i[gizmosIndexCount] = {
		0, 1,
		2, 3,
		4, 5
	};

	Matrix4x4 m[3] = { Matrix4x4(), InVMatrix, InPMatrix };

	RSI->SetUniformMatrix(m);
	RSI->SetVertexBuffer(v);
	RSI->SetIndexBuffer(i);
	RSI->DrawLinePrimitive(gizmosVertexCount, gizmosIndexCount);
}

void SoftRendererImpl3D::DrawXYPlane(Matrix4x4 InVMatrix, Matrix4x4 InPMatrix)
{
}
