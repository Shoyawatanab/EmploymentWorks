#include "pch.h"
#include "PlayerIdle.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "GameBase/Messenger/Messenger.h"
#include "Game/Messenger/MessageParams.h"


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
		Messenger::GetInstance()->Notify(MessageType::PLAYER_BOOMERANG_GET_READY_STATE);
		//�v���C���̍\���������ɑ΂��Ă̒ʒm
		Messenger::GetInstance()->Notify(MessageType::PLAYER_GET_REDAY);
		//�u�[�������̏�Ԃ��\����
		Messenger::GetInstance()->Notify(MessageType::BOOMERANG_GET_READY_STATE);


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



