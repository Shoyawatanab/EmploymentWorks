
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
#include "Game/Enemys/BossEnemy/Barrier/State/BarrierStateMachine.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="barrierDefenseAction">コントローラー</param>
/// <param name="barrier">バリア</param>
BarrierDeployment::BarrierDeployment(CommonResources* resources,
	BarrierDefenseAction* barrierDefenseAction
	,Barrier* barrier)
	:
	m_commonResources{resources}
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
void BarrierDeployment::Initialize()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
BarrierDeployment::ActionState BarrierDeployment::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	
	if (m_time >= 5.0f)
	{
		return ActionState::END;
	}
	else if (m_time >= 4.0f)
	{
		m_barrier->GetBarrierStateMachine()->ChangeState(m_barrier->GetBarrierStateMachine()->GetBarrierShrink());
	}


	m_time += elapsedTime;


	return ActionState::RUNNING;

}




/// <summary>
/// 状態に入った時
/// </summary>
void BarrierDeployment::Enter()
{
	m_time = 0;
	//バリアを有効に
	m_barrier->SetIsEntityActive(true);


}



/// <summary>
/// 状態を抜けた時
/// </summary>
void BarrierDeployment::Exit()
{

}



