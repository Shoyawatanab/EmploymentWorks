
#include "pch.h"
#include "Game/Object/Enemy/State/EnemyIdling.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player.h"

const DirectX::SimpleMath::Vector3 GENERATEDISTANCE(0.5f, 0.8f, 0.0f);

// コンストラクタ
EnemyIdling::EnemyIdling()
	:
	m_worldMatrix{},
	m_boundingSphereLeftLeg{}
{
}

// デストラクタ
EnemyIdling::~EnemyIdling()
{

}

// 初期化する
void EnemyIdling::Initialize()
{
	
	// 左脚境界球を生成する
	m_boundingSphereLeftLeg = DirectX::BoundingSphere();
	// 左脚境界球の半径を設定する
	m_boundingSphereLeftLeg.Radius = 0.01;

}


// 更新する
void EnemyIdling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


}


void EnemyIdling::Enter()
{

}

void EnemyIdling::Exit()
{

}