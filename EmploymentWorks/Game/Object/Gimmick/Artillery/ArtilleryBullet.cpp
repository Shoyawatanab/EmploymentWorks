/*
	@file	ArtilleryBullet.cpp
	@brief	
*/
#include "pch.h"
#include "ArtilleryBullet.h"
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
#include "Game/Scene/PlayScene.h"
const float SCALE(8.6f);

const float BULLETSPEED(4.0f);

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
ArtilleryBullet::ArtilleryBullet()
	:
	m_commonResources{}
	,m_scale{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
ArtilleryBullet::~ArtilleryBullet()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void ArtilleryBullet::Initialize(CommonResources* resources, PlayScene* playScene, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Scale, DirectX::SimpleMath::Quaternion Rotate)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;
	m_playScene = playScene;
	m_position = position;
	m_scale = Scale;
	m_rotate = Rotate;
	m_initialPosition = m_position;
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/ArtilleryBullet.cmo", *fx);

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, m_scale * 0.4f);
	m_bounding->CreateBoundingSphere(m_commonResources,m_position, 1.0f);

	//状態をストックにする
	m_bulletState = BulletState::Stock;


}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void ArtilleryBullet::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	DirectX::SimpleMath::Vector3 velocity;
	//速度の加算
	velocity.y += BULLETSPEED * elapsedTime;
	//回転を適用させる
	velocity = Vector3::Transform(velocity, m_rotate);

	m_position += velocity;

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void ArtilleryBullet::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
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



}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void ArtilleryBullet::Finalize()
{
	// do nothing.
}


void ArtilleryBullet::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}



void ArtilleryBullet::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(PartnerTag);
	UNREFERENCED_PARAMETER(Pos);

	switch (PartnerTag)
	{
		case CollsionObjectTag::Stage:
		case CollsionObjectTag::Enemy:
			//爆発エフェクトを生成
			m_playScene->CreateParticle(m_position);
			//初期化
			m_position = m_initialPosition;
			//状態変化
			m_bulletState = Loading;
			break;
		default:
			break;
	}

}

