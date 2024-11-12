
#include "pch.h"
#include "Game/Object/Player/State/PlayerIdling.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Observer/Messenger.h"

const float MOVE_SPEED = 5.0f;                                        //�������̃X�s�[�h
const DirectX::SimpleMath::Vector3 INITIAL_DIRECTION(0.0f, 0.0f, -1.0f); //�����̌����Ă������

void PlayerIdling::ResetGravity()
{
}

// �R���X�g���N�^
PlayerIdling::PlayerIdling()
	:
	m_commonResources{},
	m_player{}
	,m_graivty{}
{



}

// �f�X�g���N�^
PlayerIdling::~PlayerIdling()
{

}

// ����������
void PlayerIdling::Initialize()
{
	m_graivty = 0.0f;
}


// �X�V����
void PlayerIdling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;



	const auto& tracker = m_commonResources->GetInputManager()->GetMouseTracker();

	// �}�E�X�̍��{�^���������ꂽ �\����
	if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED &&
		m_player->GetUsingBoomerang()->GetBoomerangState() == m_player->GetUsingBoomerang()->GetBoomerangIdling())
	{
		//�X���[���o�̃C�x���g���Ă�
		Messenger::Notify(Messenger::SLOWMOTION);
		m_player->GetUsingBoomerang()->ChangeState(m_player->GetUsingBoomerang()->GetBoomerangGetReady());
		m_player->ChangeState(m_player->GetPlayerAttack());
	}

}


void PlayerIdling::Enter()
{

}

void PlayerIdling::Exit()
{

}

void PlayerIdling::RegistrationInformation(CommonResources* resoure, Player* player)
{
	m_commonResources = resoure;
	m_player = player;

}

