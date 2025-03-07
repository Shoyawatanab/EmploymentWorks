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




}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void PlayerAttack::Update(const float& elapsedTime)
{
	const auto& tracker = m_commonResources->GetInputManager()->GetMouseTracker();

	//������̂���߂�
	if (tracker->rightButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{

		m_player->GetPlayerStateMachine()->ChangeState(m_player->GetPlayerStateMachine()->GetPlayerIdle());

		//�u�[�������̏�Ԃ̕ύX
		Boomerang* boomerang = m_player->GetBoomerang<BoomerangGetReady>();

		boomerang->GetBoomerangStatemachine()->ChangeState(boomerang->GetBoomerangStatemachine()->GetBoomerangIdel());
		Messenger::Notify(EventParams::EventType::BoomerangGetReadyEnd, nullptr);
	}
	//������
	else if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{

		m_player->GetPlayerStateMachine()->ChangeState(m_player->GetPlayerStateMachine()->GetPlayerIdle());

		//�u�[�������𓊂���
	//�u�[�������̏�Ԃ̕ύX
		Boomerang* boomerang = m_player->GetBoomerang<BoomerangGetReady>();

		boomerang->GetBoomerangStatemachine()->ChangeState(boomerang->GetBoomerangStatemachine()->GetBoomerangThrow());
		Messenger::Notify(EventParams::EventType::BoomerangGetReadyEnd, nullptr);
		Messenger::Notify(EventParams::EventType::BoomerangThrow, nullptr);


	}


}

void PlayerAttack::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
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

		Messenger::Notify(EventParams::EventType::BoomerangGetReady, nullptr);
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



