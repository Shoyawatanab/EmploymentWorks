#include "pch.h"
#include "BossEnemy.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"
#include "GameBase/Messenger/Messenger.h"
#include "Game/Enemies/BossEnemy/BehavirTree/BossBehaviorTree.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/Model/BossEnemyModel.h"
#include "Game/Enemies/BossEnemy/Animation/BossAnimationController.h"
#include "Game/Enemies/BossEnemy/Action/BossEnemyActionManager.h"
#include "Game/Player/Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
BossEnemy::BossEnemy(Scene* scene, Player* player)
	:
	Actor(scene)
	,m_behavior{}
	,m_actionManager{}
	,m_animation{}
	,m_isGround{}
{

	using namespace DirectX::SimpleMath;

	m_rigidBody = AddComponent<RigidbodyComponent>(this);
	//当たり判定の作成
	auto aABBCollider = AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::COLLISION
		, Params::BOSSENEMY_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_SPHERE_COLLIDER_SIZE);

	Vector3 position = Vector3(0, 3.5f, -5);

	//初期状態の適用
	GetTransform()->SetScale(Vector3::One);
	GetTransform()->Translate(position);
	GetTransform()->SetRotate(Quaternion::Identity);

	//モデルの作成
	m_model = GetScene()->AddActor<BossEnemyModel>(GetScene());
	//モデルの大きさをプレイヤの設定に
	m_model->GetTransform()->SetScale(Vector3::One);
	m_model->GetTransform()->Translate(position);
	m_model->GetTransform()->SetRotate(Quaternion::Identity);
	//親子関係をセット
	m_model->GetTransform()->SetParent(GetTransform());

	//ビヘイビアツリー
	m_behavior = std::make_unique<BossBehaviorTree>(player,this);

	//アニメーションコンポーネントの追加
	m_animation = AddComponent<AnimatorComponent>(this, std::make_unique<BossAnimationController>(this));

	m_actionManager = std::make_unique<BossEnemyActionManager>(this, player);

	Messenger::GetInstance()->Rigister(
		{
			MessageType::BOSS_BEAM_ATTACK_STATE
			,MessageType::BOSS_JUMP_ATTACK_STATE
			,MessageType::BOSS_SWING_DOWN_STATE
			,MessageType::BOSS_WAKING_STATE
		}
		, this
	);

}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemy::~BossEnemy()
{

}

void BossEnemy::UpdateActor(const float& deltaTime)
{
	
	//if (m_actionManager->Update(deltaTime))
	//{
	//	//ビヘイビアツリーの更新
	//	//m_behavior->Update(deltaTime);

	//	Messenger::GetInstance()->Notify(MessageType::BOSS_JUMP_ATTACK_STATE);

	//}

	float ratio = 0.5f;

	Messenger::GetInstance()->Notify(MessageType::BOSS_DAMAGE, &ratio);

}

/// <summary>
/// 当たった時に呼ばれる関数
/// </summary>
/// <param name="collider">相手のコライダー</param>
void BossEnemy::OnCollisionEnter(ColliderComponent* collider)
{
	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			Landing();
			break;
		default:
			break;
	}

}

/// <summary>
/// 当たっているときに呼び出される関数
/// </summary>
/// <param name="collider">相手のコライダー</param>
void BossEnemy::OnCollisionStay(ColliderComponent* collider)
{
	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			Landing();
			break;
		default:
			break;
	}
}

/// <summary>
/// 離れた時に呼び出される関数
/// </summary>
/// <param name="collider"></param>
void BossEnemy::OnCollisionExit(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			m_isGround = false;
			break;
		default:
			break;
	}
}

/// <summary>
/// 着地したとき
/// </summary>
void BossEnemy::Landing()
{
	m_rigidBody->ResetGravity();
	m_isGround = true;
}
/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void BossEnemy::Notify(MessageType type, void* datas)
{

	switch (type)
	{
		case MessageType::BOSS_BEAM_ATTACK_STATE:
			break;
		case MessageType::BOSS_JUMP_ATTACK_STATE:
			break;
		case MessageType::BOSS_WAKING_STATE:
			break;
		case MessageType::BOSS_SWING_DOWN_STATE:
			break;
		default:
			break;
	}

}















