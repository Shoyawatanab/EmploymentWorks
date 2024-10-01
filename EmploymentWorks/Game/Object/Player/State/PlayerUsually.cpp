
#include "pch.h"
#include "Game/Object/Player/State/PlayerUsually.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"



const float MOVE_SPEED = 5.0f;                                        //動く時のスピード
const DirectX::SimpleMath::Vector3 INITIAL_DIRECTION(0.0f, 0.0f, -1.0f); //初期の向いている方向

// コンストラクタ
PlayerUsually::PlayerUsually()
	:
	m_player{}
	,m_graivty{}
{
}

// デストラクタ
PlayerUsually::~PlayerUsually()
{

}

// 初期化する
void PlayerUsually::Initialize()
{
	m_graivty = 0.05f;
}


// 更新する
void PlayerUsually::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	//マウスの取得
	


	// キーボードステートを取得する
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();

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


	Rotate(elapsedTime, moveDirection);

	Move(elapsedTime,   moveDirection);
	Attack(elapsedTime,  key);


	DirectX::SimpleMath::Vector3 Pos = m_player->GetPos();
	Pos.y -= m_graivty;

	m_player->SetPos(Pos);

	//// ワールド行列を更新する
	m_worldMatrix = Matrix::CreateScale(0.4f);
	//モデルが判定しているからやっている本当はBlenderで軸を決めてやる
	m_worldMatrix *= Matrix::CreateRotationY(DirectX::XMConvertToRadians(180));
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_player->GetRotate());
	m_worldMatrix *= Matrix::CreateTranslation(m_player->GetPos());


}


void PlayerUsually::Enter()
{

}

void PlayerUsually::Exit()
{

}

void PlayerUsually::RegistrationInformation(Player* player)
{

	m_player = player;

}

void PlayerUsually::Move(float elapsedTime,  DirectX::SimpleMath::Vector3 moveDirection)
{

	using namespace DirectX::SimpleMath;

	if (moveDirection == Vector3::Zero)
	{
		return;
	}

	moveDirection;
	DirectX::SimpleMath::Vector3 Pos = m_player->GetPos();

	Pos += moveDirection *= MOVE_SPEED * elapsedTime;

	m_player->SetPos(Pos);
}

void PlayerUsually::Attack(float elapsedTime, DirectX::Keyboard::State key)
{

	using namespace DirectX;
	UNREFERENCED_PARAMETER(elapsedTime);

	

	//投げる
	if (m_player->GetUsingBoomerang()->GetBoomerangState() == m_player->GetUsingBoomerang()->GetBoomerangGetReady()
		&& key.IsKeyUp(Keyboard::Keys::Space))
	{
		m_player->GetUsingBoomerang()->ChangeState(m_player->GetUsingBoomerang()->GetBoomerangThrow());
	}

	//構える
	if (m_player->GetUsingBoomerang()->GetBoomerangState() == m_player->GetUsingBoomerang()->GetBoomerangIdling()
		&& key.IsKeyDown(Keyboard::Keys::Space))
	{
		m_player->GetUsingBoomerang()->ChangeState(m_player->GetUsingBoomerang()->GetBoomerangGetReady());
	}

}

void PlayerUsually::Rotate(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection)
{

	using namespace DirectX::SimpleMath;

	if (m_player->GetUsingBoomerang()->GetBoomerangState() == m_player->GetUsingBoomerang()->GetBoomerangGetReady())
	{
		//カメラの向いている方向にプレイヤの正面を合わせる

		m_player->SetRotate(m_player->GetCameraRotate());
		m_player->SetPlayerForWard(Vector3::Transform(INITIAL_DIRECTION, m_player->GetRotate())) ;

		m_player->GetPlayerForWard().Normalize();


	}
	else
	{
		if (moveDirection == Vector3::Zero)
		{
			return;
		}
		moveDirection.Normalize();

		DirectX::SimpleMath::Vector3 Direction = m_player->GetPlayerForWard();

		//現在の向きと動く方向から軸を作る
		Vector3 axis = moveDirection.Cross(Direction);

		if (axis == Vector3::Zero)
		{
			axis = Vector3::UnitY;
		}

		//
		axis *= -1;

		float  angle = Vector3::Distance(moveDirection, Direction);
		angle *= elapsedTime * 10.0f;
		Quaternion rotation = m_player->GetRotate();
		rotation *= Quaternion::CreateFromAxisAngle(axis, angle);

		m_player->SetRotate(rotation);


		Direction = Vector3::Transform(INITIAL_DIRECTION, rotation);

		Direction.Normalize();

		m_player->SetPlayerForWard(Direction);
	}


}
