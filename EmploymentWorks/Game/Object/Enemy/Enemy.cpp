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
#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/Beam.h"


//初期のターゲットの座標の距離
const DirectX::SimpleMath::Vector3 Enemy::STAETTAEGETDIRECTION = DirectX::SimpleMath::Vector3(0, 0, 2.5f);

//敵の初期の向いている方向
const DirectX::SimpleMath::Vector3 Enemy::INITIALFORWARD = DirectX::SimpleMath::Vector3(0, 0, 1);


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
	m_targetPos{},
	m_forward{ INITIALFORWARD }

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
	
	m_initialRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, DirectX::XMConvertToRadians(90.0f));
	m_rotate = DirectX::SimpleMath::Quaternion::Identity;


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

	m_beam = std::make_unique<Beam>();
	m_beam->Initialize(m_commonResources, m_player, this);

	m_onCollisionTag = CollsionObjectTag::None;

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
	//のちに変更する　初期角度をここでやらないとプレイヤの方向に向く処理に影響が出て向かなくなる
	world *= Matrix::CreateFromQuaternion(m_initialRotate);

	world *= Matrix::CreateFromQuaternion(m_rotate);
	world *= Matrix::CreateTranslation(m_position);


	// モデルを描画する
	m_model->Draw(context, *states, world, view, projection);

	m_bounding->DrawBoundingBox(m_position, view, projection);
	m_bounding->DrawBoundingSphere(m_position, view, projection);

	m_beam->Render(view, projection);


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



IBehaviorNode::State Enemy::BeamAttack(float elapsdTime)
{

	if (m_beam->Attack(elapsdTime))
	{
		m_isAttack = true;
		//攻撃中
		return IBehaviorNode::State::Runngin;
	}

	m_isAttack = false;

	//攻撃終了
	return IBehaviorNode::State::Success;

}


void Enemy::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	//動く簿部ジェクトのタグを
	switch (PartnerTag)
	{
		case CollsionObjectTag::Boomerang:
			//ブーメランと当たっときに毎フレームHpがへらないようにする
			if (m_isCollsionTime)
			{
				return;
			}

			m_hp--;

			m_isCollsionTime = true;

		case CollsionObjectTag::Player:
		case CollsionObjectTag::Enemy:
		case CollsionObjectTag::NotMoveObject:

			m_onCollisionTag = PartnerTag;
			break;
		case CollsionObjectTag::None:
		case CollsionObjectTag::Wall:
			break;
		default:
			break;
	}

	//ブーメランとの座標から弾く方向を決める

//方向
	m_knockbackDirection = m_position - Pos;
	m_knockbackDirection.y = 0;

	m_knockbackDirection.Normalize();

	m_acceleration = 0;

}
