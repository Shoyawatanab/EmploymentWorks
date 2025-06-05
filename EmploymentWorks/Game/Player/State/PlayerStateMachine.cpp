#include "pch.h"
#include "PlayerStateMachine.h"
#include "Game/Player/Player2.h"
#include "Game/Observer/Messenger.h"
#include "Game/Player//State/PlayerStates.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerStateMachine::PlayerStateMachine(Player2* player)
{
	//Messenger::GetInstance()->Rigister<PlayerMessageType>(player->GetID(), this);
	
	//IDEL状態の追加
	AddState(PlayerState::IDEL,std::make_unique<PlayerIdle>(this, player));
	//ATTACK状態の追加
	AddState(PlayerState::ATTACK, std::make_unique<PlayerAttack>(this, player));
	//WALK状態の追加
	AddState(PlayerState::WALK, std::make_unique<PlayerWalk>(this, player));

	SetStartState(PlayerState::WALK);

}

/// <summary>
/// デストラクタ
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


