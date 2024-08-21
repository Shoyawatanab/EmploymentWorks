/*
	@file	Enemy.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Enemy.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Libraries/MyLib/Bounding.h"
#include "Game/DetectionCollision/CollisionManager.h"
#include "Game/BehaviorTree/BehaviorTree.h"
#include "Game/Object/Player.h"

//初期のターゲットの座標の距離
static const DirectX::SimpleMath::Vector3 STAETTAEGETDIRECTION = DirectX::SimpleMath::Vector3(0, 0, 2.5f);


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Enemy::Enemy()
	:
	m_commonResources{},
	m_model{},
	m_position{},
	m_hp{},
	m_behavior{},
	m_player{},
	m_knockbackDirection{},
	m_targetPos{}

{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Enemy::~Enemy()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Enemy::Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position)
{
	using namespace DirectX::SimpleMath;


	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();




	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/kariEnemy.cmo", *fx);

	m_position = position;
	

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, Vector3(3.5f, 4.9f, 1.8f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 6.0f);

	m_hp = 2;
	m_maxHP = m_hp;
	m_graivty = 0.05f;
	m_scale = 1.8f;
	m_isCollsionTime = false;
	m_collisionTime = 0;

	m_behavior = std::make_unique<BehaviorTree>(m_player, this);
	m_behavior->Initialize(m_commonResources);


	m_acceleration = 0;
	m_knockbackDirection = DirectX::SimpleMath::Vector3::Zero;
	m_knockbackTime = 0;

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Enemy::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// キーボードステートを取得する
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();

	m_behavior->Update(elapsedTime);


	if (m_isCollsionTime)
	{

		if (m_knockbackTime < 0.2f)
		{




			//弾かれる処理

			m_acceleration += 90.0f * elapsedTime;

			m_acceleration = std::min(m_acceleration, 60.0f);

			DirectX::SimpleMath::Vector3 Direction = m_knockbackDirection;

			Direction *= m_acceleration * elapsedTime;

			m_position += Direction;

		}


		m_knockbackTime += elapsedTime;

		if (m_knockbackTime >= 5)
		{
			m_isCollsionTime = false;
			m_knockbackTime = 0;
		}

	}


	if (m_hp <= 0 && m_scale > 0)
	{
		m_scale -= 0.01f;

	}
	else
	{
		m_position.y -= m_graivty;
	}


	//プレイヤと敵のベクトル
	DirectX::SimpleMath::Vector3 vec = m_player->GetPos() - m_position;
	vec.Normalize();
	//プレイヤの方向に向けるための回転
	DirectX::SimpleMath::Quaternion Rotate;

	Rotate = DirectX::SimpleMath::Quaternion::FromToRotation(STAETTAEGETDIRECTION, vec);

	DirectX::SimpleMath::Vector3 Pos = DirectX::SimpleMath::Vector3::Transform(STAETTAEGETDIRECTION, Rotate);

	m_targetPos = m_position + Pos;

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Enemy::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	// ワールド行列を更新する
	Matrix world = Matrix::CreateScale(m_scale);
	world *= Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	world *= Matrix::CreateTranslation(m_position);


	// モデルを描画する
	m_model->Draw(context, *states, world, view, projection);

	m_bounding->DrawBoundingBox(m_position, view, projection);
	m_bounding->DrawBoundingSphere(m_position, view, projection);



}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Enemy::Finalize()
{
	// do nothing.
}




void Enemy::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}

void Enemy::OnCollision(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	//ブーメランと当たっときに毎フレームHpがへらないようにする
	if (m_isCollsionTime)
	{
		return;
	}

	m_hp--;

	m_isCollsionTime = true;

	//ブーメランとの座標から弾く方向を決める

//方向
	m_knockbackDirection = m_position - Pos;
	m_knockbackDirection.y = 0;

	m_knockbackDirection.Normalize();

	m_acceleration = 0;

}
