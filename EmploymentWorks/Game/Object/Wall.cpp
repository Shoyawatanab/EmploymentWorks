/*
	@file	Wall.cpp
	@brief	
*/
#include "pch.h"
#include "Wall.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/DetectionCollision/CollisionManager.h"
#include "Libraries/MyLib/Bounding.h"

const float SCALE(8.6f);

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Wall::Wall()
	:
	m_commonResources{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Wall::~Wall()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Wall::Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position,DirectX::SimpleMath::Vector3 Extens, float Scale)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;
	m_position = position;
	m_scale = Scale;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();


	//L"Resources/Models/Wall.cmo"

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position,Extens);
	m_bounding->CreateBoundingSphere(m_commonResources,m_position, 20.0f);

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Wall::Update(float elapsedTime, DirectX::SimpleMath::Quaternion cameraRotation)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	using namespace DirectX;
	using namespace DirectX::SimpleMath;

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Wall::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	// ワールド行列を更新する
	Matrix world = Matrix::CreateScale(m_scale);
	world *= Matrix::CreateTranslation(m_position);
	//m_bounding->DrawBoundingSphere(POS, view, projection);
	m_bounding->DrawBoundingBox(m_position, view, projection);



}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Wall::Finalize()
{
	// do nothing.
}


void Wall::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}



void Wall::OnCollision()
{

}

