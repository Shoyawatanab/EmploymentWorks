#include "pch.h"
#include "BossEnemyBeam.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BossEnemy/Beam/Rays/BossEnemyBeamRays.h"
#include "Game/Enemies/BossEnemy/Beam/EnergyBall/BossEnemyBeamEnergyBall.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene"></param>
BossEnemyBeam::BossEnemyBeam(Scene* scene)
	:
	Actor(scene)
	,m_target{}
{

	//光線
	m_rays = GetScene()->AddActor<BossEnemyBeamRays>(GetScene());
	m_rays->GetTransform()->SetParent(GetTransform());

	//弾
	m_energyBall = GetScene()->AddActor<BossEnemyBeamEnergyBall>(GetScene());
	m_energyBall->GetTransform()->SetParent(GetTransform());

	GetTransform()->SetPosition(DirectX::SimpleMath::Vector3(0, 2, 0));

}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyBeam::~BossEnemyBeam()
{
}
