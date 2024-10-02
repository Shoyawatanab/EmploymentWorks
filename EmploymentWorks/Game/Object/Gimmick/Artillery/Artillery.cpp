/*
	@file	Artillery.cpp
	@brief	
*/
#include "pch.h"
#include "Artillery.h"
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

#include "Game/Object/Gimmick/Artillery/ArtilleryBase.h"
#include "Game/Object/Gimmick/Artillery/ArtilleryTurret.h"

const float SCALE(8.6f);

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Artillery::Artillery()
	:
	m_commonResources{}
	,m_scale{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Artillery::~Artillery()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Artillery::Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Scale, DirectX::SimpleMath::Vector3 Rotate)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;
	m_position = position;
	m_scale = Scale;
	m_rotate = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(Rotate.z), DirectX::XMConvertToRadians(Rotate.y), DirectX::XMConvertToRadians(Rotate.x));


	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();



	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, m_scale);
	m_bounding->CreateBoundingSphere(m_commonResources,m_position, 2.0f);

	m_base = std::make_unique<ArtilleryBase>();
	m_base->Initialize(m_commonResources, m_position, m_scale, Quaternion::Identity);

	m_turret = std::make_unique<ArtilleryTurret>();
	m_turret->Initialize(m_commonResources, m_position, m_scale, m_rotate);

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Artillery::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_base->Update(elapsedTime);

	m_turret->Update(elapsedTime);

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Artillery::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();




	// ワールド行列を更新する
	Matrix world = Matrix::CreateScale(m_scale);
	world *= Matrix::CreateFromQuaternion(m_rotate);
	world *= Matrix::CreateTranslation(m_position);



	m_bounding->DrawBoundingSphere(m_position, view, projection);
	m_bounding->DrawBoundingBox(m_position, view, projection);

	m_base->Render(view, projection);
	m_turret->Render(view, projection);

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Artillery::Finalize()
{
	// do nothing.
}


void Artillery::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}



void Artillery::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(PartnerTag);
	UNREFERENCED_PARAMETER(Pos);
}

