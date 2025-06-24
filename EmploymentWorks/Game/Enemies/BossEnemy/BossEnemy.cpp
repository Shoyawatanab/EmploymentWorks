#include "pch.h"
#include "BossEnemy.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"
#include "Game/Messenger/Messenger.h"
#include "Game/Enemies/BossEnemy/BehavirTree/BossBehaviorTree.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/Model/BossEnemyModel.h"
#include "Game/Enemies/BossEnemy/Animation/BossAnimationController.h"
#include "Game/Enemies/BossEnemy/Action/BossEnemyActionManager.h"
#include "Game/Player/Player.h"

#include "Game/Camera/PayScene/PlaySceneCamera.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="player">プレイヤ</param>
BossEnemy::BossEnemy(Scene* scene, Player* player)
	:
	EnemyBase(scene,Params::BOSSENEMY_MAX_HP)
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
	auto model = GetScene()->AddActor<BossEnemyModel>(GetScene());
	//モデルの大きさをプレイヤの設定に
	model->GetTransform()->SetScale(Vector3::One);
	model->GetTransform()->Translate(position);
	model->GetTransform()->SetRotate(Quaternion::Identity);
	//親子関係をセット
	model->GetTransform()->SetParent(GetTransform());

	SetModel(model);

	//ビヘイビアツリー
	m_behavior = std::make_unique<BossBehaviorTree>(player,this);

	//アニメーションコンポーネントの追加
	m_animation = AddComponent<AnimatorComponent>(this, std::make_unique<BossAnimationController>(this));

	m_actionManager = std::make_unique<BossEnemyActionManager>(this, player);



}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemy::~BossEnemy()
{

}

/// <summary>
/// 個別アップデート
/// </summary>
/// <param name="deltaTime"></param>
void BossEnemy::UpdateActor(const float& deltaTime)
{
	
	//if (m_actionManager->Update(deltaTime))
	//{
	//	//ビヘイビアツリーの更新
	//	//m_behavior->Update(deltaTime);

	//	Messenger::GetInstance()->Notify(MessageType::BOSS_JUMP_ATTACK_STATE);

	//}


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
		case Actor::ObjectTag::BOOMERANG:
			{
				int damage = Params::BOOMERANG_DAMAGE;

				HpDecrease(damage);
				Messenger::GetInstance()->Notify(MessageType::ENEMY_DAMAGE, &damage);
			

				float ratio = GetHpRatio();
				Messenger::GetInstance()->Notify(MessageType::BOSS_DAMAGE, &ratio);

			}

			//Hpが０になれば
			if (GetHp() <= 0)
			{

				auto camera = GetScene()->GetCamera();

				auto* playCamera = static_cast<PlaySceneCamera*>(camera);
				playCamera->SetTarget(this);

				Messenger::GetInstance()->Notify(MessageType::BOSS_DEFEATED);

			}

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

	

}















