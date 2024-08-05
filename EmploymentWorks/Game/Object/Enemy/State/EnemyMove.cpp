
#include "pch.h"
#include "Game/Object/Enemy/State/EnemyMove.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player.h"
#include "Game/Object/Enemy/Enemy.h"

const float MOVEDIRECTION = 5;


float Lerps(float a, float b, float t)
{
	return a + t * (b - a);
}

// コンストラクタ
EnemyMove::EnemyMove(Enemy* enemy)
	:
	m_worldMatrix{},
	m_boundingSphereLeftLeg{},
	m_enemy{enemy}
{
}

// デストラクタ
EnemyMove::~EnemyMove()
{

}

// 初期化する
void EnemyMove::Initialize()
{
	using namespace DirectX::SimpleMath;

	// 左脚境界球を生成する
	m_boundingSphereLeftLeg = DirectX::BoundingSphere();
	// 左脚境界球の半径を設定する
	m_boundingSphereLeftLeg.Radius = 0.01;

	Vector3 Pos = m_enemy->GetPos();


	m_startPos[0] = Vector3(0,Pos.y,Pos.z);
	m_startPos[1] = Vector3(MOVEDIRECTION, Pos.y, Pos.z);
	m_startPos[2] = Vector3(-MOVEDIRECTION, Pos.y, Pos.z);

	m_endPos[0] = Vector3(MOVEDIRECTION,Pos.y,Pos.z);
	m_endPos[1] = Vector3(-MOVEDIRECTION, Pos.y, Pos.z);
	m_endPos[2] = Vector3(0, Pos.y, Pos.z);

}


// 更新する
void EnemyMove::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;




	float PosX = Lerps(m_startPos[m_index].x, m_endPos[m_index].x, m_lerpT);

	DirectX::SimpleMath::Vector3 Pos = m_startPos[m_index];

	Pos.x = PosX;

	m_enemy->SetPos(Pos);

	m_lerpT += m_acceleration;


	if (m_lerpT > 1)
	{
		ChangePos();
		m_lerpT = 0;
	}

}

void EnemyMove::ChangePos()
{
	
	
	if (m_index >= 2)
	{
		m_enemy->ChangeState(m_enemy->GetEnemyIdling());
		return;
	}

	if (m_index == 0)
	{
		m_acceleration = 0.005;
	}

	if (m_index == 1)
	{
		m_acceleration = 0.01f;

	}


	m_index++;

}

void EnemyMove::Enter()
{
	m_lerpT = 0;
	m_index = 0;
	m_acceleration = 0.01f;
	m_startPos[m_index] = m_enemy->GetPos();
	m_endPos[m_index] = DirectX::SimpleMath::Vector3(MOVEDIRECTION,m_startPos[m_index].y,m_startPos[m_index].z);
}

void EnemyMove::Exit()
{

}