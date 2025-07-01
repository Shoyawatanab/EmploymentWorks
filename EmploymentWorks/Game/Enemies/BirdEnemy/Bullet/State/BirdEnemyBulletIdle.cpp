#include "pch.h"
#include "BirdEnemyBulletIdle.h"
#include <random>
#include "Game/Params.h"
#include "Game/Messenger/Scene/SceneMessages.h"
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

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyBulletIdle::~BirdEnemyBulletIdle()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void BirdEnemyBulletIdle::Update(const float& deltaTime)
{

	UNREFERENCED_PARAMETER(deltaTime);

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BirdEnemyBulletIdle::Enter()
{
	using namespace DirectX::SimpleMath;
	//�e�q�֌W������
	m_bullet->GetTransform()->SetParent(m_birdEnemy->GetTransform());
	//�e�Ƃ̑��Έʒu�̃Z�b�g
	m_bullet->GetTransform()->SetPosition(Vector3(0, 0, 2));
	
	//��A�N�e�B�u��
	m_bullet->SetActive(false);

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BirdEnemyBulletIdle::Exit()
{
}
