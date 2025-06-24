#include "pch.h"
#include "BirdEnemyBulletIdle.h"
#include <random>
#include "Game/Params.h"
#include "Game/Messenger/Messenger.h"
#include "Game/Enemies/BirdEnemy/Bullet/BirdEnemyBullet.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BirdEnemy/BirdEnemy.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="stateMachine">ステートマシン</param>
/// <param name="birdEnemy">鳥敵</param>
BirdEnemyBulletIdle::BirdEnemyBulletIdle(BirdEnemyBulletStateMachine* stateMachine, BirdEnemyBullet* bullet, BirdEnemy* birdEnemy)
	:
	m_stateMahine{stateMachine}
	,m_bullet{bullet}
	,m_birdEnemy{birdEnemy}
{
}

BirdEnemyBulletIdle::~BirdEnemyBulletIdle()
{
}

void BirdEnemyBulletIdle::Update(const float& deltaTime)
{


}

void BirdEnemyBulletIdle::Enter()
{
	using namespace DirectX::SimpleMath;

	m_bullet->GetTransform()->SetScale(Vector3(0.3f, 0.3f, 0.3f));
	m_bullet->GetTransform()->SetPosition(Vector3(0, 0, 1));
	m_bullet->GetTransform()->SetParent(m_birdEnemy->GetTransform());
	//非アクティブに
	//m_bullet->SetActive(false);

}

void BirdEnemyBulletIdle::Exit()
{
}
