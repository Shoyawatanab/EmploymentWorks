#include "pch.h"
#include "PlayerStateMachine.h"
#include "Game/Player/Player2.h"
#include "Game/Observer/Messenger.h"
#include "Game/Player//State/PlayerStates.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerStateMachine::PlayerStateMachine(Player2* player)
{
	//Messenger::GetInstance()->Rigister<PlayerMessageType>(player->GetID(), this);
	
	//IDEL��Ԃ̒ǉ�
	AddState(PlayerState::IDEL,std::make_unique<PlayerIdle>(this, player));
	//ATTACK��Ԃ̒ǉ�
	AddState(PlayerState::ATTACK, std::make_unique<PlayerAttack>(this, player));
	//WALK��Ԃ̒ǉ�
	AddState(PlayerState::WALK, std::make_unique<PlayerWalk>(this, player));

	SetStartState(PlayerState::WALK);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerStateMachine::~PlayerStateMachine()
{
}



//void PlayerStateMachine::Notify(const Telegram<PlayerMessageType>& telegram)
//{
//
//	switch (telegram.messageType)
//	{
//		case PlayerMessageType::IDLING:
//			//ChangeState(m_idle.get());
//			break;
//		case PlayerMessageType::ATTACK:
//			//ChangeState(m_attack.get());
//			break;
//		default:
//			break;
//	}
//
//}


