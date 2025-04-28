
#include "pch.h"
#include "BarrierClose.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/Enemys/BossEnemy/Beam/BeamRays.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"
#include "Game/Enemys/BossEnemy/Beam/BeamChargeEffect.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"

#include "Game/Enemys/BossEnemy/ActionNode/BarrierDefense/BarrierDefenseAction.h"
#include "Game/Enemys/BossEnemy/Barrier/Barrier.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
BarrierClose::BarrierClose(CommonResources* resources,
	BarrierDefenseAction* barrierDefenseAction
	,Barrier* barrier
	, BossEnemy* bossEnemy)
	:
	m_commonResources{resources}
	,m_barrierDefenseAction{ barrierDefenseAction }
	,m_barrier{barrier}
	,m_time{}
	,m_bossEnemy{bossEnemy}
{



}

/// <summary>
/// デストラクタ
/// </summary>
BarrierClose::~BarrierClose()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void BarrierClose::Initialize()
{
	


}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
BarrierClose::ActionState BarrierClose::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	
	if (m_time >= 1.0f)
	{
		m_barrierDefenseAction->ChangeState(m_barrierDefenseAction->GetBarrierIdel());
		return ActionState::End;
	}



	m_time += elapsedTime;


	return ActionState::Running;

}




/// <summary>
/// 状態に入った時
/// </summary>
void BarrierClose::Enter()
{

	m_bossEnemy->ChangeAnimation("BarrierEnd");

	m_time = 0;

}



/// <summary>
/// 状態を抜けた時
/// </summary>
void BarrierClose::Exit()
{
	m_barrier->SetIsEntityActive(false);

}



