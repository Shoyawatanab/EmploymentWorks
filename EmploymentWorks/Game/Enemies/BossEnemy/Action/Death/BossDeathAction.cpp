#include "pch.h"
#include "BossDeathAction.h"
#include "Game/Messenger/Scene/SceneMessages.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
BossDeathAction::BossDeathAction()
	:
	m_time{}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossDeathAction::~BossDeathAction()
{
	// do nothing.
}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�p�����I����</returns>
BossDeathAction:: ActionState BossDeathAction::Update(const float& deltaTime)
{
	//�A�j���[�V�������ǂ������
	if (m_time >= DEATH_TIME)
	{
		return ActionState::END;

	}


	m_time += deltaTime;

	return ActionState::RUNNING;

}



/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BossDeathAction::Enter()
{
	SceneMessenger::GetInstance()->Notify(SceneMessageType::BOSS_DEFEATED);

	m_time = 0;
}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BossDeathAction::Exit()
{
}
