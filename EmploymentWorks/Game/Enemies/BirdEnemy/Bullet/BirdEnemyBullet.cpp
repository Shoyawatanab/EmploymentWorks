#include "pch.h"
#include "BirdEnemyBullet.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BirdEnemy/BirdEnemy.h"
#include "Game/Enemies/BirdEnemy/Bullet/State/BirdEnemyBulletStateMachine.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
BirdEnemyBullet::BirdEnemyBullet(Scene* scene, BirdEnemy* birdEnemy)
	:
	Actor(scene)
	,m_birdEnemy{birdEnemy}
{

	using namespace DirectX::SimpleMath;

	//コンポーネントの追加
	AddComponent<ModelComponent>(this, "BeamEnergyBall");

	//当たり判定の作成
	AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::COLLISION
		, BOX_COLLIDER_SIZE
		, SPHERE_COLLIDER_SIZE);



	GetTransform()->SetScale(Vector3(0.3f,0.3f,0.3f));
	GetTransform()->SetPosition(Vector3(0,0,1));

	//親子関係を結ぶ
	GetTransform()->SetParent(birdEnemy->GetTransform());

	m_stateMachine = std::make_unique<BirdEnemyBulletStateMachine>(this,birdEnemy);

}


/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyBullet::~BirdEnemyBullet()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void BirdEnemyBullet::UpdateActor(const float& deltaTime)
{
	m_stateMachine->Update(deltaTime);
}

/// <summary>
/// 当たった時の関数
/// </summary>
/// <param name="collider"></param>
void BirdEnemyBullet::OnCollisionEnter(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			m_stateMachine->ChangeState(BirdEnemyBulletState::IDEL);
			break;
		default:
			break;
	}


}


