#include "pch.h"
#include "PlayerIdle.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Game/Player/Player2.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"
#include "Game/Observer/Messenger.h"


/// <summary>
/// コンストラクタ
/// </summary>
PlayerIdle::PlayerIdle(PlayerStateMachine* stateMachine, Player2* player)
	:
	m_stateMahine{stateMachine}
	,m_player{player}
{


}

/// <summary>
/// デストラクタ
/// </summary>
PlayerIdle::~PlayerIdle()
{
}




/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void PlayerIdle::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;



	////左ボタンが押されたら
	//if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	//{
	//	Messenger::GetInstance()->Notify<PlayerMessageType>(m_player->GetID(), PlayerMessageType::ATTACK);

	//}





}


/// <summary>
/// 状態に入った時
/// </summary>
void PlayerIdle::Enter()
{



}

/// <summary>
/// 状態を抜けた時
/// </summary>
void PlayerIdle::Exit()
{
}



