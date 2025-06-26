#include "pch.h"
#include "BirdEnemyBeamAttack.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Enemies/BirdEnemy/BirdEnemy.h"
#include "Game/Enemies/BirdEnemy/Bullet/BirdEnemyBullet.h"
#include "Game/Enemies/BirdEnemy/Bullet/State/BirdEnemyBulletStateMachine.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="stateMachine">�X�e�[�g�}�V��</param>
/// <param name="birdEnemy">���G</param>
BirdEnemyBeamAttack::BirdEnemyBeamAttack(BirdEnemyStateMachine* stateMachine, BirdEnemy* birdEnemy)
	:
	m_stateMahine{ stateMachine }
	, m_birdEnemy{ birdEnemy }
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyBeamAttack::~BirdEnemyBeamAttack()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void BirdEnemyBeamAttack::Update(const float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	//�e�����˂��ꂽ��X�e�[�g��؂�ւ���



}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BirdEnemyBeamAttack::Enter()
{

	//��A�N�e�B�u�̒e�̎擾
	auto bullet = m_birdEnemy->GetInactiveBullet();
	//�e�������
	if (bullet)
	{
		//��Ԃ̕ύX
		bullet->GetStateMachine()->ChangeState(BirdEnemyBulletState::CHAGE);
	}

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BirdEnemyBeamAttack::Exit()
{
}
