
#include "pch.h"
#include "BarrierDeployment.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/Enemys/BossEnemy/Beam/BeamRays.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"
#include "Game/Enemys/BossEnemy/Beam/BeamChargeEffect.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"

#include "Game/Enemys/BossEnemy/ActionNode/BarrierDefense/BarrierDefenseAction.h"
#include "Game/Enemys/BossEnemy/Barrier/Barrier.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
BarrierDeployment::BarrierDeployment(BarrierDefenseAction* barrierDefenseAction
	,Barrier* barrier)
	:
	m_commonResources{}
	,m_barrierDefenseAction{ barrierDefenseAction }
	,m_barrier{barrier}
	,m_time{}
{



}

/// <summary>
/// デストラクタ
/// </summary>
BarrierDeployment::~BarrierDeployment()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void BarrierDeployment::Initialize(CommonResources* resources)
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
IBehaviorNode::State BarrierDeployment::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	m_time += elapsedTime;



	return IBehaviorNode::State::Runngin;

}




/// <summary>
/// 状態に入った時
/// </summary>
void BarrierDeployment::Enter()
{


	m_barrier->SetIsEntityActive(true);


}



/// <summary>
/// 状態を抜けた時
/// </summary>
void BarrierDeployment::Exit()
{
	m_barrier->SetIsEntityActive(false);

}



