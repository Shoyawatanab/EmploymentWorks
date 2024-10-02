/*
	@file	ArtilleryTurret.cpp
	@brief	
*/
#include "pch.h"
#include "ArtilleryTurret.h"
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
#include "Game/Object/Gimmick//Artillery/ArtilleryBullet.h"

const float SCALE(8.6f);

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
ArtilleryTurret::ArtilleryTurret()
	:
	m_commonResources{}
	,m_scale{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
ArtilleryTurret::~ArtilleryTurret()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void ArtilleryTurret::Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Scale, DirectX::SimpleMath::Quaternion Rotate)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;
	m_position = position;
	m_scale = Scale;
	m_rotate = Rotate;


	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/ArtilleryTurret.cmo", *fx);

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, m_scale);
	m_bounding->CreateBoundingSphere(m_commonResources,m_position, 2.0f);

	//弾の生成
	for (int i = 0; i < 2; i++)
	{
		auto bullet = std::make_unique<ArtilleryBullet>();
		bullet->Initialize(m_commonResources, m_position, m_scale,m_rotate);
		m_bullet.push_back(std::move(bullet));
	}

	//一つ名の弾を装填状態にする
	m_bullet.begin()->get()->SetBulletState(ArtilleryBullet::BulletState::Loading);


}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void ArtilleryTurret::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	for (auto& bullet : m_bullet)
	{
		if (bullet->GetBulletState() == ArtilleryBullet::BulletState::Loading)
		{
			bullet->Update(elapsedTime);
		}


	}


}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void ArtilleryTurret::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();




	// ワールド行列を更新する
	Matrix world = Matrix::CreateScale(m_scale);
	world *= Matrix::CreateFromQuaternion(m_rotate);
	world *= Matrix::CreateTranslation(m_position);

	// モデルを描画する
	m_model->Draw(context, *states, world, view, projection);


	m_bounding->DrawBoundingSphere(m_position, view, projection);
	m_bounding->DrawBoundingBox(m_position, view, projection);

	//弾の描画
	for (auto& bullet : m_bullet)
	{
		if (bullet->GetBulletState() != ArtilleryBullet::BulletState::Stock)
		{
			bullet->Render(view, projection);

		}
	}


}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void ArtilleryTurret::Finalize()
{
	// do nothing.
}


void ArtilleryTurret::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}



void ArtilleryTurret::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(PartnerTag);
	UNREFERENCED_PARAMETER(Pos);
}

