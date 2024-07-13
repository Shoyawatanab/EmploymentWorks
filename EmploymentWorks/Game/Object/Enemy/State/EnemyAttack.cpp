
#include "pch.h"
#include "Game/Object/Enemy/State/EnemyAttack.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player.h"

const DirectX::SimpleMath::Vector3 GENERATEDISTANCE(0.5f, 0.8f, 0.0f);

// コンストラクタ
EnemyAttack::EnemyAttack()
	:
	m_worldMatrix{},
	m_boundingSphereLeftLeg{}
{
}

// デストラクタ
EnemyAttack::~EnemyAttack()
{

}

// 初期化する
void EnemyAttack::Initialize()
{
	
	// 左脚境界球を生成する
	m_boundingSphereLeftLeg = DirectX::BoundingSphere();
	// 左脚境界球の半径を設定する
	m_boundingSphereLeftLeg.Radius = 0.01;

}


// 更新する
void EnemyAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;



}


void EnemyAttack::Enter()
{

}

void EnemyAttack::Exit()
{

}