#include "pch.h"
#include "PlayerStateMachine.h"
#include "Game/Player/Player.h"
#include "Game/Player//State/PlayerStates.h"
#include "Game/Messenger/Messenger.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerStateMachine::PlayerStateMachine(Player* player)
{
	//Messenger::GetInstance()->Rigister<PlayerMessageType>(player->GetID(), this);
	
	//IDEL��Ԃ̒ǉ�
	AddState(PlayerState::IDEL,std::make_unique<PlayerIdle>(this, player));
	//BOOMERANG_ATTACK��Ԃ̒ǉ�
	AddState(PlayerState::BOOMERANG_ATTACK, std::make_unique<PlayerBoomerangAttack>(this, player));
	//BOOMERANG_GETREADY���
	AddState(PlayerState::BOOMERANG_GET_READY, std::make_unique<PlayerBoomerangGetReady>(this, player));

	SetStartState(PlayerState::IDEL);

	//���b�Z�[�W�̓o�^
	Messenger::GetInstance()->Rigister(
		{
		 MessageType::PLAYER_IDLE_STATE
		,MessageType::PLAYER_BOOMERANG_ATTACK_STATE
		,MessageType::PLAYER_BOOMERANG_GET_READY_STATE
		}
		, this
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerStateMachine::~PlayerStateMachine()
{
}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void PlayerStateMachine::Notify(MessageType type, void* datas)
{

	switch (type)
	{
		case MessageType::PLAYER_IDLE_STATE:
			ChangeState(PlayerState::IDEL);
			break;
		case MessageType::PLAYER_BOOMERANG_GET_READY_STATE:
			ChangeState(PlayerState::BOOMERANG_GET_READY);
			break;
		case MessageType::PLAYER_BOOMERANG_ATTACK_STATE:
			ChangeState(PlayerState::BOOMERANG_ATTACK);
			break;
		default:
			break;
	}

}


