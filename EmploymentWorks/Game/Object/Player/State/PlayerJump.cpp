
#include "pch.h"
#include "Game/Object/Player/State/PlayerJump.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"

const float MOVE_SPEED = 5.0f;                                        //動く時のスピード
const DirectX::SimpleMath::Vector3 INITIAL_DIRECTION(0.0f, 0.0f, -1.0f); //初期の向いている方向

void PlayerJump::ResetGravity()
{
}

// コンストラクタ
PlayerJump::PlayerJump()
	:
	m_player{}
{



}

// デストラクタ
PlayerJump::~PlayerJump()
{

}

// 初期化する
void PlayerJump::Initialize()
{
}


// 更新する
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
