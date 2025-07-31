/*
	�N���X��     : PlayerIdle
	����         : �v���C���̃u�[�������ʏ���
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "PlayerIdle.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Messenger/Messenger.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerIdle::PlayerIdle(PlayerStateMachine* stateMachine, Player* player)
	:
	m_stateMahine{stateMachine}
	,m_player{player}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerIdle::~PlayerIdle()
{
}




/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void PlayerIdle::Update(const float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	using namespace DirectX;

	const auto& tracker = CommonResources::GetInstance()->GetInputManager()->GetMouseTracker();


	//���{�^���������ꂽ��
	if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		//�ʒm
		//�v���C���̏�Ԃɂ��Ă̒ʒm
		Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::PLAYER_BOOMERANG_GET_READY_STATE);
		//�v���C���̍\���������ɑ΂��Ă̒ʒm
		Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::PLAYER_GET_REDAY);
		//�u�[�������̏�Ԃ��\����
		Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::BOOMERANG_GET_READY_STATE);


	}





}


/// <summary>
/// ��Ԃɓ�������
/// </summary>
void PlayerIdle::Enter()
{



}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void PlayerIdle::Exit()
{
}



