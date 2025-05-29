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
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
PlayerAttack::~PlayerAttack()
{
}



/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void PlayerAttack::Initialize(CommonResources* resources)
{
	m_commonResources = resources;

	Messenger::GetInstance()->Rigister(GamePlayMessageType::MOUSE_WHEEL_UP, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::MOUSE_WHEEL_DOWN, this);

	m_throwState = ThrowState::RIGHT;


}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void PlayerAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;

	const auto& tracker = m_commonResources->GetInputManager()->GetMouseTracker();

	//�������̕ύX

	//������̂���߂�
	if (tracker->rightButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{

		m_player->GetPlayerStateMachine()->ChangeState(m_player->GetPlayerStateMachine()->GetPlayerIdle());

		//�u�[�������̏�Ԃ̕ύX
		Boomerang* boomerang = m_player->GetBoomerang<BoomerangGetReady>();

		boomerang->GetBoomerangStatemachine()->ChangeState(boomerang->GetBoomerangStatemachine()->GetBoomerangIdel());
		Messenger::GetInstance()->Notify(::GamePlayMessageType::BOOMERANG_GET_READY_END, nullptr);
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
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
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

		Messenger::GetInstance()->Notify(::GamePlayMessageType::BOOMERANG_GET_READY, nullptr);
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
		default:
			break;
	}

}



