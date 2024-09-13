
#include "pch.h"
#include "Game/Object/Player/State/PlayerBlownAway.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"




// コンストラクタ
PlayerBlownAway::PlayerBlownAway()
	:
	m_boomerang{},
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

	m_position = m_player->GetPos();

	m_position += m_direction * 6 * elapsedTime;

	m_position.y -= m_graivty * elapsedTime;

	m_player->SetPos(m_position);

	//重力の加算
	m_graivty += 4.0f * elapsedTime;

	//// ワールド行列を更新する
	m_worldMatrix = Matrix::CreateScale(0.4f);
	//モデルが判定しているからやっている本当はBlenderで軸を決めてやる
	m_worldMatrix *= Matrix::CreateRotationY(DirectX::XMConvertToRadians(180));
	//m_worldMatrix *= Matrix::CreateFromQuaternion(m_player->GetRotate());
	m_worldMatrix *= Matrix::CreateTranslation(m_player->GetPos());


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

void PlayerBlownAway::RegistrationInformation(Boomerang* boomerang, Player* player)
{

	m_boomerang = boomerang;
	m_player = player;

}

