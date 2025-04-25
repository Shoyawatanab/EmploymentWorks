
#include "pch.h"
#include "BarrierIdel.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/Enemys/BossEnemy/Beam/BeamRays.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"
#include "Game/Enemys/BossEnemy/Beam/BeamChargeEffect.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"

#include "Game/Enemys/BossEnemy/ActionNode/BarrierDefense/BarrierDefenseAction.h"
/// <summary>
/// コンストラクタ
/// </summary>
BarrierIdel::BarrierIdel(BarrierDefenseAction* barrierDefenseAction)
	:
	m_commonResources{}
	, m_barrierDefenseAction{ barrierDefenseAction }
{



}

/// <summary>
/// デストラクタ
/// </summary>
BarrierIdel::~BarrierIdel()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void BarrierIdel::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
IBehaviorNode::State BarrierIdel::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_barrierDefenseAction->ChangeState(m_barrierDefenseAction->GetBarrierPreliminaryAction());

	return IBehaviorNode::State::Runngin;


}




/// <summary>
/// 状態に入った時
/// </summary>
void BarrierIdel::Enter()
{


}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BarrierIdel::Exit()
{

}



