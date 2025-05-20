
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


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="barrierDefenseAction">コントローラー</param>
/// <param name="barrier">バリは</param>
/// <param name="owner">所有者</param>
BarrierClose::BarrierClose(CommonResources* resources,
	BarrierDefenseAction* barrierDefenseAction
	,Barrier* barrier
	, CharacterEntity* owner)
	:
	m_commonResources{resources}
	,m_barrierDefenseAction{ barrierDefenseAction }
	,m_barrier{barrier}
	,m_time{}
	, m_owner{owner}
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
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
BarrierClose::ActionState BarrierClose::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	
	if (m_time >= CLOSE_TIME)
	{
		return ActionState::END;
	}


	m_time += elapsedTime;


	return ActionState::RUNNING;

}


/// <summary>
/// 状態に入った時
/// </summary>
void BarrierClose::Enter()
{

	m_owner->ChangeAnimation("BarrierEnd");

	m_time = 0;

}



/// <summary>
/// 状態を抜けた時
/// </summary>
void BarrierClose::Exit()
{
	m_barrier->SetIsEntityActive(false);

}



