
#include "pch.h"
#include "Game/Object/Player/State/PlayerJump.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"

const float MOVE_SPEED = 5.0f;                                        //�������̃X�s�[�h
const DirectX::SimpleMath::Vector3 INITIAL_DIRECTION(0.0f, 0.0f, -1.0f); //�����̌����Ă������

void PlayerJump::ResetGravity()
{
}

// �R���X�g���N�^
PlayerJump::PlayerJump()
	:
	m_player{}
{



}

// �f�X�g���N�^
PlayerJump::~PlayerJump()
{

}

// ����������
void PlayerJump::Initialize()
{
}


// �X�V����
void PlayerJump::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	


}


void PlayerJump::Enter()
{
	
	DirectX::SimpleMath::Vector3 velocity = m_player->GetVelocity();
	velocity.y = 0.25f;
	m_player->SetVelocity(velocity);


}

void PlayerJump::Exit()
{

}

void PlayerJump::RegistrationInformation(CommonResources* resoure, Player* player)
{
	m_commonResources = resoure;
	m_player = player;

}
