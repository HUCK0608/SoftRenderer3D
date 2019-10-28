
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
	VertexData v[vertexCount] = {
		// Front
		VertexData(Vector3(0.5f, -0.5f, 0.5f)),
		VertexData(Vector3(0.5f, 0.5f, 0.5f)),
		VertexData(Vector3(0.5f, 0.5f, -0.5f)),
		VertexData(Vector3(0.5f, -0.5f, -0.5f)),
		// Left
		VertexData(Vector3(-0.5f, -0.5f, 0.5f)),
		VertexData(Vector3(-0.5f, 0.5f, 0.5f)),
		VertexData(Vector3(0.5f, 0.5f, 0.5f)),
		VertexData(Vector3(0.5f, -0.5f, 0.5f)),
		// Right
		VertexData(Vector3(0.5f, -0.5f, -0.5f)),
		VertexData(Vector3(0.5f, 0.5f, -0.5f)),
		VertexData(Vector3(-0.5f, 0.5f, -0.5f)),
		VertexData(Vector3(-0.5f, -0.5f, -0.5f)),
		// Back
		VertexData(Vector3(-0.5f, -0.5f, -0.5f)),
		VertexData(Vector3(-0.5f, 0.5f, -0.5f)),
		VertexData(Vector3(-0.5f, 0.5f, 0.5f)),
		VertexData(Vector3(-0.5f, -0.5f, 0.5f)),
		// Top
		VertexData(Vector3(0.5f, 0.5f, 0.5f)),
		VertexData(Vector3(-0.5f, 0.5f, 0.5f)),
		VertexData(Vector3(-0.5f, 0.5f, -0.5f)),
		VertexData(Vector3(0.5f, 0.5f, -0.5f)),
		// Bottom
		VertexData(Vector3(-0.5f, -0.5f, 0.5f)),
		VertexData(Vector3(0.5f, -0.5f, 0.5f)),
		VertexData(Vector3(0.5f, -0.5f, -0.5f)),
		VertexData(Vector3(-0.5f, -0.5f, -0.5f))
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
	
}

void SoftRendererImpl3D::UpdateImpl(float DeltaSeconds)
{
	// 모델링 변환 행렬
	static GameObject quad;
	quad.GetTransform().SetScale(Vector3::One * 100.f);

	static float moveSpeed = 100.f;
	static float rotationSpeed = 180.f;

	quad.GetTransform().AddPosition(Vector3::UnitZ * (InputManager.GetYAxis() * moveSpeed * DeltaSeconds));
	quad.GetTransform().AddRotation(Vector3::UnitY * (InputManager.GetXAxis() * rotationSpeed * DeltaSeconds));

	Matrix4x4 TRSMat = quad.GetTransform().GetTRS();

	Camera camera;
	camera.GetGameObject().GetTransform().SetPosition(Vector3(0.f, 500.f, -500.f));
}
