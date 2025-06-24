#include "pch.h"
#include "BirdEnemyBeamAttack.h"
#include "Game/Messenger/Messenger.h"


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
	
	//�e�����˂��ꂽ��X�e�[�g��؂�ւ���



}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BirdEnemyBeamAttack::Enter()
{
	//�e���`���[�W��
	Messenger::GetInstance()->Notify(MessageType::BIRD_BULLET_CHAGE_STATE);
}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BirdEnemyBeamAttack::Exit()
{
}
