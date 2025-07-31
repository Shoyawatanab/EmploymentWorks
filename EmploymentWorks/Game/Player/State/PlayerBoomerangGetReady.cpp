/*
	�N���X��     : PlayerBoomerangGetReady
	����         : �v���C���̃u�[�������\�����
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "PlayerBoomerangAttack.h"
#include "PlayerBoomerangGetReady.h"
#include "GameBase/Common/Commons.h"
#include "Game/Messenger/Scene/SceneMessages.h"
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
	UNREFERENCED_PARAMETER(deltaTime);
	using namespace DirectX;


	const auto& tracker = CommonResources::GetInstance()->GetInputManager()->GetMouseTracker();

	//�������̕ύX

	//������̂���߂�
	if (tracker->rightButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		//�v���C���̏�Ԃ�IDEL��
		Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::PLAYER_IDLE_STATE);
		//�v���C���̍\���I���̒ʒm
		Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::PLAYER_GET_REDAY_END);
		//�u�[�������̏�Ԃ�ʏ��
		Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::BOOMERANG_IDEL_STATE);

	}
	//������
	else if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		//�u�[�������̏�Ԃ�THROW��
		Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::BOOMERANG_THROW_STATE);
		//�v���C���̏�Ԃ�ATTACK��
		Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::PLAYER_BOOMERANG_ATTACK_STATE);
		//�v���C���̍\���̏I���̒ʒm
		Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::PLAYER_GET_REDAY_END);
		//�u�[�������𓊂�������
		Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::BOOMERANG_THROW);



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
