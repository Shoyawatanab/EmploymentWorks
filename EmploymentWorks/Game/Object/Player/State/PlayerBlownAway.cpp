
#include "pch.h"
#include "Game/Object/Player/State/PlayerBlownAway.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"




// �R���X�g���N�^
PlayerBlownAway::PlayerBlownAway()
	:
	m_boomerang{},
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

	m_position = m_player->GetPos();

	m_position += m_direction * 6 * elapsedTime;

	m_position.y -= m_graivty * elapsedTime;

	m_player->SetPos(m_position);

	//�d�͂̉��Z
	m_graivty += 4.0f * elapsedTime;

	//// ���[���h�s����X�V����
	m_worldMatrix = Matrix::CreateScale(0.4f);
	//���f�������肵�Ă��邩�����Ă���{����Blender�Ŏ������߂Ă��
	m_worldMatrix *= Matrix::CreateRotationY(DirectX::XMConvertToRadians(180));
	//m_worldMatrix *= Matrix::CreateFromQuaternion(m_player->GetRotate());
	m_worldMatrix *= Matrix::CreateTranslation(m_player->GetPos());


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

void PlayerBlownAway::RegistrationInformation(Boomerang* boomerang, Player* player)
{

	m_boomerang = boomerang;
	m_player = player;

}

