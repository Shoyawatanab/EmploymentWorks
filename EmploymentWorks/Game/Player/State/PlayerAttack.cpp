#include "pch.h"
#include "PlayerAttack.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Observer/Messenger.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
PlayerAttack::PlayerAttack()
	:
	m_commonResources{}
	,m_position{}
	,m_scale{}
	,m_rotation{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
PlayerAttack::~PlayerAttack()
{
}


/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="player">プレイヤ</param>
void PlayerAttack::AddPointer(Player* player)
{
	m_player = player;
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void PlayerAttack::Initialize(CommonResources* resources)
{
	m_commonResources = resources;

	Messenger::GetInstance()->Rigister(GameMessageType::MouseWheelUp, this);
	Messenger::GetInstance()->Rigister(GameMessageType::MouseWheelDown, this);

	m_throwState = ThrowState::Right;


}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void PlayerAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	const auto& tracker = m_commonResources->GetInputManager()->GetMouseTracker();

	//投げ方の変更

	//投げるのをやめる
	if (tracker->rightButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{

		m_player->GetPlayerStateMachine()->ChangeState(m_player->GetPlayerStateMachine()->GetPlayerIdle());

		//ブーメランの状態の変更
		Boomerang* boomerang = m_player->GetBoomerang<BoomerangGetReady>();

		boomerang->GetBoomerangStatemachine()->ChangeState(boomerang->GetBoomerangStatemachine()->GetBoomerangIdel());
		Messenger::GetInstance()->Notify(::GameMessageType::BoomerangGetReadyEnd, nullptr);
	}
	//投げる
	else if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{

		m_player->GetPlayerStateMachine()->ChangeState(m_player->GetPlayerStateMachine()->GetPlayerIdle());



		//ブーメランを投げる
	//ブーメランの状態の変更
		Boomerang* boomerang = m_player->GetBoomerang<BoomerangGetReady>();

		switch (m_throwState)
		{
			case PlayerAttack::ThrowState::Right:
				boomerang->GetBoomerangStatemachine()->ChangeState(boomerang->GetBoomerangStatemachine()->GetBoomerangRightThrow());
				break;
			case PlayerAttack::ThrowState::Left:
				boomerang->GetBoomerangStatemachine()->ChangeState(boomerang->GetBoomerangStatemachine()->GetBoomerangLeftThrow());
				break;
			case PlayerAttack::ThrowState::Front:
				boomerang->GetBoomerangStatemachine()->ChangeState(boomerang->GetBoomerangStatemachine()->GetBoomerangFrontThrow());
				break;
			default:
				break;
		}

		Messenger::GetInstance()->Notify(::GameMessageType::BoomerangGetReadyEnd, nullptr);
		Messenger::GetInstance()->Notify(::GameMessageType::BoomerangThrow, nullptr);


	}


}

void PlayerAttack::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}

/// <summary>
/// 状態に入った時
/// </summary>
void PlayerAttack::Enter()
{

	//ブーメランの状態の変更
	Boomerang* boomerang = m_player->GetBoomerang<BoomerangIdle>();

	//ブーメランが投げれるなら
	if (boomerang)
	{
		boomerang->GetBoomerangStatemachine()->ChangeState(boomerang->GetBoomerangStatemachine()->GetBoomerangGetReady());

		Messenger::GetInstance()->Notify(::GameMessageType::BoomerangGetReady, nullptr);
		//プレイヤのアニメーションの変更
		m_player->ChangeAnimation("GetReady");

	}
	else
	{
		//投げれるブーメランがないとき
		m_player->GetPlayerStateMachine()->ChangeState(m_player->GetPlayerStateMachine()->GetPlayerIdle());

	}


}


/// <summary>
/// 状態を抜けた時
/// </summary>
void PlayerAttack::Exit()
{


}

void PlayerAttack::Notify(const Telegram<GameMessageType>& telegram)
{
	

	switch (telegram.messageType)
	{
		case ::GameMessageType::MouseWheelUp:
		{
			switch (m_throwState)
			{
				case PlayerAttack::ThrowState::Right:
					break;
				case PlayerAttack::ThrowState::Front:
					m_throwState = ThrowState::Right;
					break;
				case PlayerAttack::ThrowState::Left:
					m_throwState = ThrowState::Front;
					break;
				default:
					break;
			}

			Messenger::GetInstance()->Notify(::GameMessageType::ChangeBoomerangThrowState, &m_throwState);
		}
			break;
		case ::GameMessageType::MouseWheelDown:
		{
			switch (m_throwState)
			{
				case PlayerAttack::ThrowState::Right:
					m_throwState = ThrowState::Front;
					break;
				case PlayerAttack::ThrowState::Front:
					m_throwState = ThrowState::Left;
					break;
				case PlayerAttack::ThrowState::Left:
					break;
				default:
					break;
			}

			Messenger::GetInstance()->Notify(::GameMessageType::ChangeBoomerangThrowState, &m_throwState);
		}
			break;
		default:
			break;
	}

}



