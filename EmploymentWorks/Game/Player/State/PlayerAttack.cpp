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

	Messenger::Attach(EventParams::EventType::MouseWheelUp, this);
	Messenger::Attach(EventParams::EventType::MouseWheelDown, this);

	m_throwState = ThrowState::Right;


}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void PlayerAttack::Update(const float& elapsedTime)
{
	const auto& tracker = m_commonResources->GetInputManager()->GetMouseTracker();

	//投げ方の変更

	//投げるのをやめる
	if (tracker->rightButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{

		m_player->GetPlayerStateMachine()->ChangeState(m_player->GetPlayerStateMachine()->GetPlayerIdle());

		//ブーメランの状態の変更
		Boomerang* boomerang = m_player->GetBoomerang<BoomerangGetReady>();

		boomerang->GetBoomerangStatemachine()->ChangeState(boomerang->GetBoomerangStatemachine()->GetBoomerangIdel());
		Messenger::Notify(EventParams::EventType::BoomerangGetReadyEnd, nullptr);
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

		Messenger::Notify(EventParams::EventType::BoomerangGetReadyEnd, nullptr);
		Messenger::Notify(EventParams::EventType::BoomerangThrow, nullptr);


	}


}

void PlayerAttack::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
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

		Messenger::Notify(EventParams::EventType::BoomerangGetReady, nullptr);
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

void PlayerAttack::Notify(EventParams::EventType type, void* datas)
{

	switch (type)
	{
		case EventParams::EventType::MouseWheelUp:
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


			EventParams::ChangeBoomerangThrowStateDatas data = { static_cast<int>(m_throwState) };

			Messenger::Notify(EventParams::EventType::ChangeBoomerangThrowState, &data);
		}
			break;
		case EventParams::EventType::MouseWheelDown:
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

			EventParams::ChangeBoomerangThrowStateDatas data = { static_cast<int>(m_throwState) };

			Messenger::Notify(EventParams::EventType::ChangeBoomerangThrowState, &data);
		}
			break;
		default:
			break;
	}

}



