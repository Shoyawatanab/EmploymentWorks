
#include "pch.h"
#include "Game/Object/Boomerang/State/BoomerangIdling.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"

const DirectX::SimpleMath::Vector3 GENERATEDISTANCE(0.5f, 0.8f, 0.0f);

// コンストラクタ
BoomerangIdling::BoomerangIdling()
	:
	m_worldMatrix{},
	m_boundingSphereLeftLeg{},
	m_boomerang{},
	m_player{}
{
}

// デストラクタ
BoomerangIdling::~BoomerangIdling()
{

}

// 初期化する
void BoomerangIdling::Initialize()
{
	


}


// 更新する
void BoomerangIdling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	m_boomerang->SetRotate(m_player->GetRotate());
	//m_boomerang->SetPosition(m_player->GetPosition() + GENERATEDISTANCE);

	//マトリクス　子供の計算　親の計算の順番でやらないといけない
	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());
	
	m_worldMatrix *= Matrix::CreateRotationZ(XMConvertToRadians(90));  //ブーメランを立てるように９０度回転

	m_worldMatrix *= Matrix::CreateTranslation(GENERATEDISTANCE);
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_player->GetRotate());
	m_worldMatrix *= Matrix::CreateTranslation(m_player->GetPosition());

	//座標を更新
	Vector3 Pos = Vector3::Transform(Vector3::Zero, m_worldMatrix);
	m_boomerang->SetPosition(Pos);

}


void BoomerangIdling::Enter()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_boomerang->SetRotate(m_player->GetRotate());
	//m_boomerang->SetPosition(m_player->GetPosition() + GENERATEDISTANCE);

	//マトリクス　子供の計算　親の計算の順番でやらないといけない
	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());

	m_worldMatrix *= Matrix::CreateRotationZ(XMConvertToRadians(90));  //ブーメランを立てるように９０度回転

	m_worldMatrix *= Matrix::CreateTranslation(GENERATEDISTANCE);
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_player->GetRotate());
	m_worldMatrix *= Matrix::CreateTranslation(m_player->GetPosition());

	//座標を更新
	Vector3 Pos = Vector3::Transform(Vector3::Zero, m_worldMatrix);
	m_boomerang->SetPosition(Pos);

}

void BoomerangIdling::Exit()
{

	//using namespace DirectX;
	//using namespace DirectX::SimpleMath;

	//m_boomerang->SetRotate(m_player->GetRotate());
	////m_boomerang->SetPosition(m_player->GetPosition() + GENERATEDISTANCE);

	////マトリクス　子供の計算　親の計算の順番でやらないといけない
	//m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());

	//m_worldMatrix *= Matrix::CreateRotationZ(XMConvertToRadians(90));  //ブーメランを立てるように９０度回転

	//m_worldMatrix *= Matrix::CreateTranslation(GENERATEDISTANCE);
	//m_worldMatrix *= Matrix::CreateFromQuaternion(m_player->GetRotate());
	//m_worldMatrix *= Matrix::CreateTranslation(m_player->GetPosition());


	////座標を更新
	//Vector3 Pos = Vector3::Transform(Vector3::Zero, m_worldMatrix);
	//m_boomerang->SetPosition(Pos);


}

void BoomerangIdling::RegistrationInformation(Boomerang* boomerang, Player* player)
{

	m_boomerang = boomerang;
	m_player = player;

}
