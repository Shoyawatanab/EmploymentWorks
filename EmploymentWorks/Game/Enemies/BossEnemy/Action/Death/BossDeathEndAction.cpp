/*
	�N���X��     : BossDeathActionController
	����         : �{�X�G�̓|�����Ƃ��̏I�����
	�⑫�E���ӓ_ : ����ȍ~Action�̍X�V����
*/
#include "pch.h"
#include "BossDeathEndAction.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Enemies/EnemyManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
BossDeathEndAction::BossDeathEndAction(BossEnemy* bossEnemy)
	:
	m_bossEnemy{bossEnemy}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossDeathEndAction::~BossDeathEndAction()
{
	// do nothing.
}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�p�����I����</returns>
BossDeathEndAction::ActionState BossDeathEndAction::Update(const float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	return ActionState::RUNNING;

}



/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BossDeathEndAction::Enter()
{
	
	//�}�l�[�W���[�Ɏ��S�̒ʒm
	m_bossEnemy->GetEnemyManger()->DeathEnemy(m_bossEnemy);

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BossDeathEndAction::Exit()
{
}
