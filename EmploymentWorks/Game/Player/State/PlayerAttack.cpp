#include "pch.h"
#include "PlayerAttack.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Observer/Messenger.h"



/// <summary>
/// コンストラクタ
/// </summary>
PlayerAttack::PlayerAttack(Player* player)
	:
	m_commonResources{}
	,m_position{}
	,m_scale{}
	,m_rotation{}
	,m_player{player}
{

}

/// <summary>
/// デストラクタ
/// </summary>
PlayerAttack::~PlayerAttack()
{
}



/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void PlayerAttack::Initialize(CommonResources* resources)
{
	m_commonResources = resources;

	Messenger::GetInstance()->Rigister(GamePlayMessageType::MOUSE_WHEEL_UP, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::MOUSE_WHEEL_DOWN, this);

	m_throwState = ThrowState::RIGHT;


}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void PlayerAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;

	const auto& tracker = m_commonResources->GetInputManager()->GetMouseTracker();

	//投げ方の変更

	//投げるのをやめる
	if (tracker->rightButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{

		m_player->GetPlayerStateMachine()->ChangeState(m_player->GetPlayerStateMachine()->GetPlayerIdle());

		//ブーメランの状態の変更
		Boomerang* boomerang = m_player->GetBoomerang<BoomerangGetReady>();

		boomerang->GetBoomerangStatemachine()->ChangeState(boomerang->GetBoomerangStatemachine()->GetBoomerangIdel());
		Messenger::GetInstance()->Notify(::GamePlayMessageType::BOOMERANG_GET_READY_END, nullptr);
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
			case PlayerAttack::ThrowState::RIGHT:
				boomerang->GetBoomerangStatemachine()->ChangeState(boomerang->GetBoomerangStatemachine()->GetBoomerangRightThrow());
				break;
			case PlayerAttack::ThrowState::LEFT:
				boomerang->GetBoomerangStatemachine()->ChangeState(boomerang->GetBoomerangStatemachine()->GetBoomerangLeftThrow());
				break;
			case PlayerAttack::ThrowState::FRONT:
				boomerang->GetBoomerangStatemachine()->ChangeState(boomerang->GetBoomerangStatemachine()->GetBoomerangFrontThrow());
				break;
			default:
				break;
		}

		Messenger::GetInstance()->Notify(::GamePlayMessageType::BOOMERANG_GET_READY_END, nullptr);
		Messenger::GetInstance()->Notify(::GamePlayMessageType::BOOMERANG_THTROW, nullptr);


	}


}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
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

		Messenger::GetInstance()->Notify(::GamePlayMessageType::BOOMERANG_GET_READY, nullptr);
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

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="telegram">データ</param>
void PlayerAttack::Notify(const Telegram<GamePlayMessageType>& telegram)
{
	

	switch (telegram.messageType)
	{
		case ::GamePlayMessageType::MOUSE_WHEEL_UP:
		{
			switch (m_throwState)
			{
				case PlayerAttack::ThrowState::FRONT:
					m_throwState = ThrowState::RIGHT;
					break;
				case PlayerAttack::ThrowState::LEFT:
					m_throwState = ThrowState::FRONT;
					break;
				default:
					break;
			}

			Messenger::GetInstance()->Notify(::GamePlayMessageType::CHARGE_BOOMERANG_THROW_STATE, &m_throwState);
		}
			break;
		case ::GamePlayMessageType::MOUSE_WHEEL_DOWN:
		{
			switch (m_throwState)
			{
				case PlayerAttack::ThrowState::RIGHT:
					m_throwState = ThrowState::FRONT;
					break;
				case PlayerAttack::ThrowState::FRONT:
					m_throwState = ThrowState::LEFT;
					break;
				default:
					break;
			}

			Messenger::GetInstance()->Notify(::GamePlayMessageType::CHARGE_BOOMERANG_THROW_STATE, &m_throwState);
		}
			break;
		default:
			break;
	}

}



