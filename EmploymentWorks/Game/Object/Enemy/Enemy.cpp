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

const int MAXHP = 10;

//ビーム攻撃の予備動作時間
const float BEAMATTACKPRELIMINRRYACTIONTIME = 2.0f;

const float WALKMAXSPEED = 2.0f;

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

	//auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();




	//// モデルを読み込む準備
	//std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	//fx->SetDirectory(L"Resources/Models");

	//// モデルを読み込む
	//m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemy.cmo", *fx);

	//m_position = initialPosition;

	m_initialRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, DirectX::XMConvertToRadians(90.0f));
	m_rotate = DirectX::SimpleMath::Quaternion::Identity;

	//m_rotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180.0f));

	m_boundingBoxCenter = Vector3(0, 1, 0);

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position + m_boundingBoxCenter, Vector3(4.5f, 5.5f, 1.8f));
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

	m_rightHandPos = m_position + Vector3(-1.5f,-3, 7.50);

	m_beamStartPosition = Vector3::Transform(m_rightHandPos, m_rotate);

	//m_hp = 7;
	//攻撃の予備動作時間の初期化
	m_preliminaryActionTime = 0;

	//Walk関係の変数の初期化
	m_walkSpeed = 0.0f;
	m_walkAccelration = 5.0f;
	m_stepDuration = 0.5f;
	m_stepTime = 0.0f;
	m_isStep = true;

	//JumpAttack
	m_jumpHeight = 3.0f;
	m_jumpAttackTime = 0;
	m_transformRatio = 0;

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Enemy::Update(float elapsedTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsedTime);


	// キーボードステートトラッカーを取得する
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	//デバック用
	if (kbTracker->released.Q)
	{
		m_hp = 1;
	}


	m_behavior->Update(elapsedTime);


	//部品を更新する
	BossEnemyBase::Update(elapsedTime);

	BossEnemyBase::AnimationUdate(elapsedTime);



	//m_rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.1f))
	//ビームの開始地点を求める
	m_beamStartPosition = Vector3::Transform(m_rightHandPos, m_rotate) + m_position;

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
	DirectX::SimpleMath::Vector3 vec = m_player->GetPosition() - m_position;
	vec.Normalize();
	//プレイヤの方向に向けるための回転
	DirectX::SimpleMath::Quaternion Rotate;

	Rotate = DirectX::SimpleMath::Quaternion::FromToRotation(STAETTAEGETDIRECTION, vec);

	DirectX::SimpleMath::Vector3 Pos = DirectX::SimpleMath::Vector3::Transform(STAETTAEGETDIRECTION, Rotate);

	m_targetPos = m_position + Pos;

	m_bounding->Update(m_position + m_boundingBoxCenter);

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Enemy::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace DirectX::SimpleMath;

	//auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	//auto states = m_commonResources->GetCommonStates();


	//// ワールド行列を更新する
	//m_worldMatrix = Matrix::CreateScale(m_scale);
	////のちに変更する　初期角度をここでやらないとプレイヤの方向に向く処理に影響が出て向かなくなる
	//m_worldMatrix *= Matrix::CreateFromQuaternion(m_initialRotate);

	//m_worldMatrix *= Matrix::CreateFromQuaternion(m_rotate);
	//m_worldMatrix *= Matrix::CreateTranslation(m_position);

	//部品を描画する
	BossEnemyBase::Render(view, projection);

	// モデルを描画する
	//m_model->Draw(context, *states, world, view, projection);

	m_bounding->DrawBoundingBox(view, projection);
	m_bounding->DrawBoundingSphere(view, projection);

	if (m_hp > 0)
	{
		m_beam->Render(view, projection);

	}


}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Enemy::Finalize()
{
	// do nothing.
}

//大きさを小さくする
Animation::AnimationState  Enemy::FallDwonAnimation(float elapsdTime)
{

	UNREFERENCED_PARAMETER(elapsdTime);

	Animation::AnimationState state;

	state = BossEnemyBase::AnimationUdate(elapsdTime);


	//部品を更新する
	BossEnemyBase::Update(elapsdTime);






	if (state == Animation::AnimationState::Running)
	{
		m_position.y += 2.0f *elapsdTime;

		DirectX::SimpleMath::Vector3 velocity = m_forward *  0.5f * elapsdTime;

		

		m_position += velocity;
		

		m_boundingBoxCenter.y += 0.95f * elapsdTime;
	}

	m_position.y -= m_graivty;


	//プレイヤと敵のベクトル
	DirectX::SimpleMath::Vector3 vec = m_player->GetPosition() - m_position;
	vec.Normalize();
	//プレイヤの方向に向けるための回転
	DirectX::SimpleMath::Quaternion Rotate;

	Rotate = DirectX::SimpleMath::Quaternion::FromToRotation(STAETTAEGETDIRECTION, vec);

	DirectX::SimpleMath::Vector3 Pos = DirectX::SimpleMath::Vector3::Transform(STAETTAEGETDIRECTION, Rotate);

	m_targetPos = m_position + Pos;

	m_bounding->Update(m_position + m_boundingBoxCenter);

	return state;

}

void Enemy::SetAnimation(std::string name)
{

	//RegistrationRungingAnimation("FallDown");

	SetRunnginAnimationName("FallDown");

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

//歩きの関数
void Enemy::Walk(float elapsdTime)
{

	//プレイヤの座標の取得
	DirectX::SimpleMath::Vector3 playerPosition = m_player->GetPosition();

	//方向を求める
	DirectX::SimpleMath::Vector3 direction = playerPosition - m_position;

	//正規化
	direction.Normalize();

	//
	if (m_isStep)
	{

		m_walkSpeed += m_walkAccelration * elapsdTime;

		m_walkSpeed = std::min(m_walkSpeed, WALKMAXSPEED);

		direction *= m_walkSpeed * elapsdTime;

		m_position += direction;

		m_stepTime += elapsdTime;

		//1歩が終了したら
		if (m_stepTime >= m_stepDuration)
		{
			m_isStep = false;
			m_walkSpeed = 0.0f;
			m_stepTime = 0.0f;
		}

	}
	else if(!m_isStep)
	{

		m_stepTime += elapsdTime;

		if (m_stepTime >= m_stepDuration)
		{
			m_isStep = true;
			m_stepTime = 0.0f;
		}

	}
}

/// <summary>
/// ジャンプして踏みつける攻撃
/// </summary>
/// <param name="elapstTime"></param>
IBehaviorNode::State Enemy::JumpAttack(float elapstTime)
{
	using namespace DirectX::SimpleMath;

	//初めの１回だけ呼びたい
	if (!m_isAttack)
	{
		m_jumpHeight = 2.0f;
		m_isAttack = true;
		//プレイヤの座標を初期値に
		m_jumpPosition.push_back(m_position);
		//中間座標を求める
		DirectX::SimpleMath::Vector3 middlePosition = (m_player->GetPosition() - m_position) / 2;
		middlePosition += m_position;
		//高さを指定したものに変更する
		middlePosition.y = m_jumpHeight + m_position.y;
		//中間座標を登録
		m_jumpPosition.push_back(middlePosition );

		DirectX::SimpleMath::Vector3 targetPosition = m_player->GetPosition();
		targetPosition.y = m_position.y;
		//最終座標を登録
		m_jumpPosition.push_back(targetPosition);
		//中間地点のｙ座標を反転させる
		middlePosition.y *= -1;
		//４つ目の座標を登録
		m_jumpPosition.push_back(middlePosition);

		m_jumpAttackIndex =static_cast<int>( m_jumpPosition.size() - 1);

	}

	//予備動作
	if (m_preliminaryActionTime < 2)
	{

		m_preliminaryActionTime += elapstTime;

		return IBehaviorNode::State::Runngin;

	}


	//距離を求める
	float distance = (m_jumpPosition[(m_jumpAttackIndex + 2) % m_jumpPosition.size()] -
		m_jumpPosition[(m_jumpAttackIndex + 1) % m_jumpPosition.size()]).Length();
	//移動割合
	m_transformRatio = m_jumpAttackTime * 5.0f / distance;

	m_transformRatio = std::min(m_transformRatio, 1.0f);

	DirectX::SimpleMath::Vector3  Pos = Vector3::CatmullRom(
		m_jumpPosition[(m_jumpAttackIndex + 0) % m_jumpPosition.size()],
		m_jumpPosition[(m_jumpAttackIndex + 1) % m_jumpPosition.size()],
		m_jumpPosition[(m_jumpAttackIndex + 2) % m_jumpPosition.size()],
		m_jumpPosition[(m_jumpAttackIndex + 3) % m_jumpPosition.size()],
		m_transformRatio
	);

	m_position = Pos;

	//割合が１を超えたら次の点に移動
	if (m_transformRatio >= 1.0f)
	{
		m_jumpAttackIndex++;
		m_jumpAttackTime = 0.0f;
	}

	//最後の点についたらプレイヤを追いかける処理に切り替える
	if (m_jumpAttackIndex >= m_jumpPosition.size() + 1)
	{

		m_jumpPosition.clear();
		m_isAttack = false;
		m_preliminaryActionTime = 0;
		m_jumpAttackTime = 0;


		Vector3 playerPosition = m_player->GetPosition();
		Vector3 enemyPosition = m_position;

		//高さを考慮しないため
		playerPosition.y = 0;
		enemyPosition.y = 0;

		//ダメージ範囲内かどうか
		float distance = Vector3::Distance(enemyPosition,playerPosition);

		if (distance <= 2)
		{
			int hp = m_player->GetPlayerHP();
			hp -= 1;
			m_player->SetPlayerHP(hp);
		}


		return IBehaviorNode::State::Success;

	}

	m_jumpAttackTime += elapstTime;

	//攻撃中
	return IBehaviorNode::State::Runngin;
}




void Enemy::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);

	BossEnemyBase::RegistrationCollionManager(collsionManager);
}



IBehaviorNode::State Enemy::BeamAttack(float elapsdTime)
{
	//攻撃の初めに1回だけ予備隊
	if (m_preliminaryActionTime == 0)
	{
		//アニメーションの登録
		SetRunnginAnimationName("Beam");
	}


	//予備動作時間ないかどうか
	if (m_preliminaryActionTime < BEAMATTACKPRELIMINRRYACTIONTIME)
	{
		//予備動作時間の加算
		m_preliminaryActionTime += elapsdTime;
		FacingThePlayer(elapsdTime);
		//攻撃中
		return IBehaviorNode::State::Runngin;
	}


	if (m_beam->Attack(elapsdTime))
	{
		m_isAttack = true;
		//攻撃中
		return IBehaviorNode::State::Runngin;
	}
	//攻撃かどうかの初期化
	m_isAttack = false;

	//攻撃の予備動作時間の初期化
	m_preliminaryActionTime = 0;

	//攻撃終了
	return IBehaviorNode::State::Success;

}

/// <summary>
/// 近距離攻撃　ビヘイビアツリーないで呼び出す
/// </summary>
/// <returns></returns>
IBehaviorNode::State Enemy::CloseRangeAttack(float elapsdTime)
{



	return JumpAttack(elapsdTime);
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

void Enemy::FacingThePlayer(float elapsdTime)
{

	//向きたい方向
	DirectX::SimpleMath::Vector3 direction = m_player->GetPosition() - m_position;
	direction.Normalize();
	//今の敵の前方向
	DirectX::SimpleMath::Vector3 forward = m_forward;
	//forward.Normalize();

	DirectX::SimpleMath::Vector3 moveAxis = forward.Cross(direction);

	if (moveAxis.y >= 0.0f)
	{
		moveAxis = DirectX::SimpleMath::Vector3::Up;
	}
	else
	{
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//角度を求める
	float moveAngle = forward.Dot(direction);

	//if (moveAngle < 0.01f)
	//{
	//	return IBehaviorNode::State::Failure;
	//}

//ラジアン値に変換
	moveAngle = acosf(moveAngle);

	//角度と速度の比較で小さいほうを取得
	moveAngle = std::min(moveAngle, 1.0f * elapsdTime);

	//敵の回転の取得
	DirectX::SimpleMath::Quaternion Rotate = m_rotate;
	//Y軸に対して回転をかける
	Rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	m_rotate = Rotate;

	//回転をもとに敵の初期の方向ベクトルの更新
	forward = DirectX::SimpleMath::Vector3::Transform(Enemy::INITIALFORWARD, Rotate);
	forward.Normalize();
	m_forward = forward;


}
