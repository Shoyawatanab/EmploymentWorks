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
#include "Game/Object/Enemy/BossEnemy/BossEnemyBottom.h"


//初期のターゲットの座標の距離
const DirectX::SimpleMath::Vector3 Enemy::STAETTAEGETDIRECTION = DirectX::SimpleMath::Vector3(0, 0, 2.5f);

//敵の初期の向いている方向
const DirectX::SimpleMath::Vector3 Enemy::INITIALFORWARD = DirectX::SimpleMath::Vector3(0, 0, 1);

const int MAXHP = 1;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Enemy::Enemy(CommonResources* resources, IComponent* parent, const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BossEnemyBase(resources, parent, initialScale, DirectX::SimpleMath::Vector3::Zero, initialAngle),
	m_commonResources{resources},
	//m_model{},
	m_position{initialPosition},
	m_hp{},
	m_behavior{},
	m_player{},
	m_knockbackDirection{},
	m_targetPos{},
	m_forward{ INITIALFORWARD }
	,m_acceleration{}
	,m_collisionTime{}
	,m_graivty{}
	,m_isAttack{}
	,m_isCollsionTime{}
	,m_knockbackTime{}
	,m_maxHP{}
	,m_onCollisionTag{}
	,m_scale{}
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
void Enemy::Initialize()
{
	using namespace DirectX::SimpleMath;



	//m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();




	//// モデルを読み込む準備
	//std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	//fx->SetDirectory(L"Resources/Models");

	//// モデルを読み込む
	//m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemy.cmo", *fx);

	//m_position = initialPosition;

	m_initialRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, DirectX::XMConvertToRadians(90.0f));
	m_rotate = DirectX::SimpleMath::Quaternion::Identity;


	m_bounding->CreateBoundingBox(m_commonResources, m_position + Vector3(0,1,0), Vector3(4.5f, 5.5f, 1.8f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 6.0f);

	m_hp = MAXHP;
	m_maxHP = m_hp;
	m_graivty = 0.05f;
	//m_scale = 1.8f / 100;
	m_scale = Vector3(1.5f, 1.5f, 1.5f);
	m_isCollsionTime = false;
	m_collisionTime = 0;

	m_behavior->Initialize(m_commonResources);


	m_acceleration = 0;
	m_knockbackDirection = DirectX::SimpleMath::Vector3::Zero;
	m_knockbackTime = 0;

	m_beam->Initialize(m_commonResources, m_player, this);

	m_onCollisionTag = CollsionObjectTag::None;

	//「Bottom」を生成する
	Attach(std::make_unique<BossEnemyBottom>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(0.0f, -0.6f, 0.0f), Quaternion::Identity));

	RegistrationRungingAnimation("Beam");

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

	BossEnemyBase::AnimationUdate(elapsedTime);


	//部品を更新する
	BossEnemyBase::Update(elapsedTime);


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


	m_position.y -= m_graivty;


	//プレイヤと敵のベクトル
	DirectX::SimpleMath::Vector3 vec = m_player->GetPos() - m_position;
	vec.Normalize();
	//プレイヤの方向に向けるための回転
	DirectX::SimpleMath::Quaternion Rotate;

	Rotate = DirectX::SimpleMath::Quaternion::FromToRotation(STAETTAEGETDIRECTION, vec);

	DirectX::SimpleMath::Vector3 Pos = DirectX::SimpleMath::Vector3::Transform(STAETTAEGETDIRECTION, Rotate);

	m_targetPos = m_position + Pos;

	m_bounding->Update(m_position + DirectX::SimpleMath::Vector3(0,1,0));

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Enemy::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	// ワールド行列を更新する
	m_worldMatrix = Matrix::CreateScale(m_scale);
	//のちに変更する　初期角度をここでやらないとプレイヤの方向に向く処理に影響が出て向かなくなる
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_initialRotate);

	m_worldMatrix *= Matrix::CreateFromQuaternion(m_rotate);
	m_worldMatrix *= Matrix::CreateTranslation(m_position);

	//部品を描画する
	BossEnemyBase::Render(view, projection);

	// モデルを描画する
	//m_model->Draw(context, *states, world, view, projection);

	m_bounding->DrawBoundingBox(view, projection);
	m_bounding->DrawBoundingSphere(view, projection);

	m_beam->Render(view, projection);


}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Enemy::Finalize()
{
	// do nothing.
}

//大きさを小さくする
void Enemy::ReduceSize(float elapsdTime)
{

	UNREFERENCED_PARAMETER(elapsdTime);

	//m_scale -= 0.01f;
	//m_scale = std::max(m_scale, 0.0f);
}

void Enemy::RegistrationInformation( Player* player)
{

	m_player = player;
	
	m_behavior->RegistrationInformation(m_player, this);

}


void Enemy::Instances()
{

	m_bounding = std::make_unique<Bounding>();
	m_behavior = std::make_unique<BehaviorTree>();
	m_beam = std::make_unique<Beam>();


}




void Enemy::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);

	BossEnemyBase::RegistrationCollionManager(collsionManager);
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
			break;
		case CollsionObjectTag::ArtilleryBullet:
			
			m_hp -= 2;

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
