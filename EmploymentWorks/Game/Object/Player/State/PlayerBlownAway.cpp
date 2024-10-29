
#include "pch.h"
#include "Game/Object/Player/State/PlayerBlownAway.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"




void PlayerBlownAway::ResetGravity()
{
}

// コンストラクタ
PlayerBlownAway::PlayerBlownAway()
	:
	m_player{}
{
}

// デストラクタ
PlayerBlownAway::~PlayerBlownAway()
{

}

// 初期化する
void PlayerBlownAway::Initialize()
{

}


// 更新する
void PlayerBlownAway::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_position = m_player->GetPosition();

	m_position += m_direction * 6 * elapsedTime;

	m_position.y -= m_graivty * elapsedTime;

	m_player->SetPosition(m_position);

	//重力の加算
	m_graivty += 4.0f * elapsedTime;



}


void PlayerBlownAway::Enter()
{

	//飛ぶ方向
	m_direction = m_player->GetBlownAwayDirection();

	//m_direction = DirectX::SimpleMath::Vector3::Backward;
	//重力
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

