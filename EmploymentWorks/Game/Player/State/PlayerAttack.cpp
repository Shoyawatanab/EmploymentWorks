#include "pch.h"
#include "PlayerAttack.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Observer/Messenger.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerAttack::PlayerAttack(PlayerStateMachine* stateMachine, Player2* player)
	:
	m_stateMahine{stateMachine}
	,m_player{player}
	,m_throwState{}
	,m_throwQuantityState{}
{
	Messenger::GetInstance()->Rigister(GamePlayMessageType::MOUSE_WHEEL_UP, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::MOUSE_WHEEL_DOWN, this);

	Messenger::GetInstance()->Rigister(GamePlayMessageType::CHANGE_THROW_COUNT, this);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerAttack::~PlayerAttack()
{
}



/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void PlayerAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;



}



/// <summary>
/// ��Ԃɓ�������
/// </summary>
void PlayerAttack::Enter()
{


}


/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void PlayerAttack::Exit()
{


}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="telegram">�f�[�^</param>
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
		case GamePlayMessageType::CHANGE_THROW_COUNT:
			
			switch (m_throwQuantityState)
			{
				case PlayerAttack::ThrowQuantityState::ONE:
					m_throwQuantityState = ThrowQuantityState::THREE;
					break;
				case PlayerAttack::ThrowQuantityState::THREE:
					m_throwQuantityState = ThrowQuantityState::ONE;
					break;
				default:
					break;
			}

			break;

		default:
			break;
	}

}



