
#include "pch.h"
#include "RisingPillarIdel.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/Enemys/BossEnemy/Beam/BeamRays.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"
#include "Game/Enemys/BossEnemy/Beam/BeamChargeEffect.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"

#include "Game/Enemys/BossEnemy/ActionNode/RisingPillar/RisingPillarvAction.h"
/// <summary>
/// コンストラクタ
/// </summary>
RisingPillarIdel::RisingPillarIdel(RisingPillarvAction* risingPillarvAction )
	:
	m_commonResources{}
	,m_risingPillarvAction{risingPillarvAction}
{



}

/// <summary>
/// デストラクタ
/// </summary>
RisingPillarIdel::~RisingPillarIdel()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void RisingPillarIdel::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
IBehaviorNode::State RisingPillarIdel::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_risingPillarvAction->ChangeState(m_risingPillarvAction->GetPillarpreliminaryAction());

	return IBehaviorNode::State::Runngin;


}




/// <summary>
/// 状態に入った時
/// </summary>
void RisingPillarIdel::Enter()
{


}

/// <summary>
/// 状態を抜けた時
/// </summary>
void RisingPillarIdel::Exit()
{

}



