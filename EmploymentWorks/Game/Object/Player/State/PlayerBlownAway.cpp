
#include "pch.h"
#include "Game/Object/Player/State/PlayerBlownAway.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"




void PlayerBlownAway::ResetGravity()
{
}

// �R���X�g���N�^
PlayerBlownAway::PlayerBlownAway()
	:
	m_player{}
{
}

// �f�X�g���N�^
PlayerBlownAway::~PlayerBlownAway()
{

}

// ����������
void PlayerBlownAway::Initialize()
{

}


// �X�V����
void PlayerBlownAway::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_position = m_player->GetPosition();

	m_position += m_direction * 6 * elapsedTime;

	m_position.y -= m_graivty * elapsedTime;

	m_player->SetPosition(m_position);

	//�d�͂̉��Z
	m_graivty += 4.0f * elapsedTime;



}


void PlayerBlownAway::Enter()
{

	//��ԕ���
	m_direction = m_player->GetBlownAwayDirection();

	//m_direction = DirectX::SimpleMath::Vector3::Backward;
	//�d��
	m_graivty = -2.0f;

	m_position += m_direction;

}

void PlayerBlownAway::Exit()
{

}

void PlayerBlownAway::RegistrationInformation(CommonResources* resoure, Player* player)
{
	m_commonResources = resoure;
	m_player = player;

}

