#include "pch.h"
#include "BossEnemy.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Enemies/BossEnemy/BehavirTree/BossBehaviorTree.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/Model/BossEnemyModel.h"
#include "Game/Enemies/BossEnemy/Animation/BossAnimationController.h"
#include "Game/Enemies/BossEnemy/Action/BossEnemyActionManager.h"
#include "Game/Player/Player.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Enemies/BossEnemy/Beam/BossEnemyBeam.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="player">プレイヤ</param>
BossEnemy::BossEnemy(Scene* scene, DirectX::SimpleMath::Vector3 scale
	, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation
	, Player* player)
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
	AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::COLLISION
		, Params::BOSSENEMY_BOX_COLLIDER_SIZE * scale
		, Params::BOSSENEMY_SPHERE_COLLIDER_SIZE * std::max({scale.x,scale.y,scale.y}));

	//モデルの作成
	auto model = GetScene()->AddActor<BossEnemyModel>(GetScene());
	//親子関係をセット
	model->GetTransform()->SetParent(GetTransform());

	SetModel(model);



	//初期状態の適用
	GetTransform()->SetScale(scale);
	GetTransform()->Translate(position);
	GetTransform()->SetRotate(rotation);

	auto beam = GetScene()->AddActor<BossEnemyBeam>(GetScene());
	beam->GetTransform()->SetParent(GetTransform());


	//ビヘイビアツリー
	m_behavior = std::make_unique<BossBehaviorTree>(player,this);

	//アニメーションコンポーネントの追加
	m_animation = AddComponent<AnimatorComponent>(this, std::make_unique<BossAnimationController>(this));

	m_actionManager = std::make_unique<BossEnemyActionManager>(this,player,beam);



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
	
	if (FadeManager::GetInstance()->GetIsFade())
	{
		return;
	}

	if (m_actionManager->Update(deltaTime))
	{
		//ビヘイビアツリーの更新
		//m_behavior->Update(deltaTime);

		SceneMessenger::GetInstance()->Notify(SceneMessageType::BOSS_BEAM_ATTACK_STATE);

	}


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
				SceneMessenger::GetInstance()->Notify(SceneMessageType::ENEMY_DAMAGE, &damage);
			

				float ratio = GetHpRatio();
				SceneMessenger::GetInstance()->Notify(SceneMessageType::BOSS_DAMAGE, &ratio);

			}

			//Hpが０になれば
			if (GetHp() <= 0)
			{

				auto camera = GetScene()->GetCamera();

				auto* playCamera = static_cast<PlaySceneCamera*>(camera);
				playCamera->SetTarget(this);

				SceneMessenger::GetInstance()->Notify(SceneMessageType::BOSS_DEFEATED);

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
















