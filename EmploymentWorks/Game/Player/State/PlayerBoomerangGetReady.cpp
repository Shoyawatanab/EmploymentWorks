#include "pch.h"
#include "PlayerBoomerangAttack.h"
#include "PlayerBoomerangGetReady.h"
#include "GameBase/Common/Commons.h"
#include "Game/Messenger/Messenger.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="stateMachine">�X�e�[�g�}�V�[��</param>
/// <param name="player">�v���C��</param>
PlayerBoomerangGetReady::PlayerBoomerangGetReady(PlayerStateMachine* stateMachine, Player* player)
	:
	m_player{player}
	,m_stateMahine{stateMachine}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerBoomerangGetReady::~PlayerBoomerangGetReady()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void PlayerBoomerangGetReady::Update(const float& deltaTime)
{
	using namespace DirectX;


	const auto& tracker = CommonResources::GetInstance()->GetInputManager()->GetMouseTracker();

	//�������̕ύX

	//������̂���߂�
	if (tracker->rightButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		//�v���C���̏�Ԃ�IDEL��
		Messenger::GetInstance()->Notify(MessageType::PLAYER_IDLE_STATE);
		//�v���C���̍\���I���̒ʒm
		Messenger::GetInstance()->Notify(MessageType::PLAYER_GET_REDAY_END);
		//�u�[�������̏�Ԃ�ʏ��
		Messenger::GetInstance()->Notify(MessageType::BOOMERANG_IDEL_STATE);

	}
	//������
	else if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		//�u�[�������̏�Ԃ�THROW��
		Messenger::GetInstance()->Notify(MessageType::BOOMERANG_THROW_STATE);
		//�v���C���̏�Ԃ�ATTACK��
		Messenger::GetInstance()->Notify(MessageType::PLAYER_BOOMERANG_ATTACK_STATE);
		//�v���C���̍\���̏I���̒ʒm
		Messenger::GetInstance()->Notify(MessageType::PLAYER_GET_REDAY_END);


	}
}


/// <summary>
/// ��Ԃɓ�������
/// </summary>
void PlayerBoomerangGetReady::Enter()
{
}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void PlayerBoomerangGetReady::Exit()
{
}
