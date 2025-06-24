#include "pch.h"
#include "BirdEnemyBulletIdle.h"
#include <random>
#include "Game/Params.h"
#include "Game/Messenger/Messenger.h"
#include "Game/Enemies/BirdEnemy/Bullet/BirdEnemyBullet.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BirdEnemy/BirdEnemy.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="stateMachine">�X�e�[�g�}�V��</param>
/// <param name="birdEnemy">���G</param>
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
	//��A�N�e�B�u��
	//m_bullet->SetActive(false);

}

void BirdEnemyBulletIdle::Exit()
{
}
