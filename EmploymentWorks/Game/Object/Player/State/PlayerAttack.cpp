
#include "pch.h"
#include "Game/Object/Player/State/PlayerAttack.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"

const float MOVE_SPEED = 5.0f;                                        //�������̃X�s�[�h
const DirectX::SimpleMath::Vector3 INITIAL_DIRECTION(0.0f, 0.0f, -1.0f); //�����̌����Ă������

void PlayerAttack::ResetGravity()
{
}

// �R���X�g���N�^
PlayerAttack::PlayerAttack()
	:
	m_player{}
	,m_graivty{}
{



}

// �f�X�g���N�^
PlayerAttack::~PlayerAttack()
{

}

// ����������
void PlayerAttack::Initialize()
{
	m_graivty = 0.0f;
}


// �X�V����
void PlayerAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	//�}�E�X�̎擾
	


	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();
	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	Vector3 moveDirection = Vector3::Zero;

	if (key.IsKeyDown(Keyboard::Keyboard::W))
	{
		moveDirection.z--;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::S))
	{
		moveDirection.z++;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::A))
	{
		moveDirection.x--;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::D))
	{
		moveDirection.x++;
	}

	moveDirection = Vector3::Transform(moveDirection, m_player->GetCameraRotate());


	Attack(elapsedTime,  key);













}


void PlayerAttack::Enter()
{

}

void PlayerAttack::Exit()
{

}

void PlayerAttack::RegistrationInformation(CommonResources* resoure, Player* player)
{
	m_commonResources = resoure;
	m_player = player;

}

void PlayerAttack::Attack(float elapsedTime, DirectX::Keyboard::State key)
{

	using namespace DirectX;
	UNREFERENCED_PARAMETER(elapsedTime);
	UNREFERENCED_PARAMETER(key);

	const auto& tracker = m_commonResources->GetInputManager()->GetMouseTracker();

	//������
	//if (m_player->GetUsingBoomerang()->GetBoomerangState() == m_player->GetUsingBoomerang()->GetBoomerangGetReady()
	//	&& key.IsKeyUp(Keyboard::Keys::Space))
	//{
	//	m_player->GetUsingBoomerang()->ChangeState(m_player->GetUsingBoomerang()->GetBoomerangThrow());
	//}

	//�\����
	//if (m_player->GetUsingBoomerang()->GetBoomerangState() == m_player->GetUsingBoomerang()->GetBoomerangIdling()
	//	&& key.IsKeyDown(Keyboard::Keys::Space))
	//{
	//	m_player->GetUsingBoomerang()->ChangeState(m_player->GetUsingBoomerang()->GetBoomerangGetReady());
	//}


		// �}�E�X�̍��{�^���������ꂽ
	if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED &&
		m_player->GetUsingBoomerang()->GetBoomerangState() == m_player->GetUsingBoomerang()->GetBoomerangGetReady())
	{
		m_player->GetUsingBoomerang()->ChangeState(m_player->GetUsingBoomerang()->GetBoomerangThrow());
		m_player->ChangeState(m_player->GetPlayerIding());

	}



	////�\����
	//	// �}�E�X�̍��{�^���������ꂽ
	//if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED &&
	//	m_player->GetUsingBoomerang()->GetBoomerangState() == m_player->GetUsingBoomerang()->GetBoomerangIdling())
	//{
	//	m_player->GetUsingBoomerang()->ChangeState(m_player->GetUsingBoomerang()->GetBoomerangGetReady());
	//}

}

