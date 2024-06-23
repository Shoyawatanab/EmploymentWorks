
#include "pch.h"
#include "Game/Object/Boomerang/State/BoomerangGetReady.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player.h"

const DirectX::SimpleMath::Vector3 GENERATEDISTANCE(0.5f, 0.8f, 0.0f);

const float HOLDANGLE = 45.0f;

// コンストラクタ
BoomerangGetReady::BoomerangGetReady(Boomerang* boomerang, Player* player)
	:
	m_worldMatrix{},
	m_boundingSphereLeftLeg{},
	m_boomerang{boomerang},
	m_player{player}
{
}

// デストラクタ
BoomerangGetReady::~BoomerangGetReady()
{

}

// 初期化する
void BoomerangGetReady::Initialize()
{
	
	// 左脚境界球を生成する
	m_boundingSphereLeftLeg = DirectX::BoundingSphere();
	// 左脚境界球の半径を設定する
	m_boundingSphereLeftLeg.Radius = 0.01;

}



// 更新する
void BoomerangGetReady::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	m_boomerang->SetRotate(m_player->GetRotate()) ;
	m_boomerang->SetPosition(m_player->GetPosition());


	//マトリクス　子供の計算　親の計算の順番でやらないといけない
	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());
	m_worldMatrix *= Matrix::CreateTranslation(GENERATEDISTANCE);
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_boomerang->GetRotate());
	m_worldMatrix *= Matrix::CreateTranslation(m_boomerang->GetPosition());

}


void BoomerangGetReady::Enter()
{
	using namespace DirectX::SimpleMath;
	Quaternion angle = m_boomerang->GetRotate();

	//Y,X,Zの順番
	angle *= Quaternion::CreateFromYawPitchRoll(0, 100.5f, 0);

   	m_boomerang->SetRotate(angle);


}

void BoomerangGetReady::Exit()
{

}