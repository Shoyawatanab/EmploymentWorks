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
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
PlayerAttack::~PlayerAttack()
{
}


/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="player">�v���C��</param>
void PlayerAttack::AddPointer(Player* player)
{
	m_player = player;
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void PlayerAttack::Initialize(CommonResources* resources)
{
	m_commonResources = resources;

	Messenger::GetInstance()->Rigister(GameMessageType::MouseWheelUp, this);
	Messenger::GetInstance()->Rigister(GameMessageType::MouseWheelDown, this);

	m_throwState = ThrowState::Right;


}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void PlayerAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	const auto& tracker = m_commonResources->GetInputManager()->GetMouseTracker();

	//�������̕ύX

	//������̂���߂�
	if (tracker->rightButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{

		m_player->GetPlayerStateMachine()->ChangeState(m_player->GetPlayerStateMachine()->GetPlayerIdle());

		//�u�[�������̏�Ԃ̕ύX
		Boomerang* boomerang = m_player->GetBoomerang<BoomerangGetReady>();

		boomerang->GetBoomerangStatemachine()->ChangeState(boomerang->GetBoomerangStatemachine()->GetBoomerangIdel());
		Messenger::GetInstance()->Notify(::GameMessageType::BoomerangGetReadyEnd, nullptr);
	}
	//������
	else if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{

		m_player->GetPlayerStateMachine()->ChangeState(m_player->GetPlayerStateMachine()->GetPlayerIdle());



		//�u�[�������𓊂���
	//�u�[�������̏�Ԃ̕ύX
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
/// ��Ԃɓ�������
/// </summary>
void PlayerAttack::Enter()
{

	//�u�[�������̏�Ԃ̕ύX
	Boomerang* boomerang = m_player->GetBoomerang<BoomerangIdle>();

	//�u�[���������������Ȃ�
	if (boomerang)
	{
		boomerang->GetBoomerangStatemachine()->ChangeState(boomerang->GetBoomerangStatemachine()->GetBoomerangGetReady());

		Messenger::GetInstance()->Notify(::GameMessageType::BoomerangGetReady, nullptr);
		//�v���C���̃A�j���[�V�����̕ύX
		m_player->ChangeAnimation("GetReady");

	}
	else
	{
		//�������u�[���������Ȃ��Ƃ�
		m_player->GetPlayerStateMachine()->ChangeState(m_player->GetPlayerStateMachine()->GetPlayerIdle());

	}


}


/// <summary>
/// ��Ԃ𔲂�����
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



