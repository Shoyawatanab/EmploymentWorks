
#include "pch.h"
#include "RisingPillarRise.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/Enemys/BossEnemy/Beam/BeamRays.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"
#include "Game/Enemys/BossEnemy/Beam/BeamChargeEffect.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"

#include "Game/StageObject/Pillar/Pillar.h"
#include "Game/Enemys/BossEnemy/ActionNode/RisingPillar/RisingPillarvAction.h"

#include "Game/StageObject/StageObjectManager.h"
#include "Game/StageObject/Pillar/Pillar.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
RisingPillarRise::RisingPillarRise(RisingPillarvAction* risingPillarvAction, StageObjectManager* stageObjectManager)
	:
	m_commonResources{}
	, m_pillar{}
	,m_stageObjectManager{stageObjectManager}
	,m_risingPillarvAction{risingPillarvAction}
{



}

/// <summary>
/// デストラクタ
/// </summary>
RisingPillarRise::~RisingPillarRise()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void RisingPillarRise::Initialize(CommonResources* resources)
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
IBehaviorNode::State RisingPillarRise::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	Vector3 scale = m_pillar->GetLocalScale();

	scale.z += elapsedTime * 10.0f;

	scale.z = std::min(scale.z, 10.0f);

	m_pillar->SetLocalScale(scale);

	if (scale.z >= 10.0f)
	{
		m_risingPillarvAction->ChangeState(m_risingPillarvAction->GetPillarIdel());
		return IBehaviorNode::State::Success;
	}

	return IBehaviorNode::State::Runngin;

}




/// <summary>
/// 状態に入った時
/// </summary>
void RisingPillarRise::Enter()
{

	auto pillars = m_stageObjectManager->GetStageObjects("Pillar");

	for(auto& pillar: *pillars)
	{
		if (!pillar->GetIsEntityActive())
		{
			m_pillar = pillar.get();
			break;
		}
	}

	if (m_pillar)
	{
		m_pillar->SetIsEntityActive(true);
	}
	else
	{
		m_risingPillarvAction->ChangeState(m_risingPillarvAction->GetPillarIdel());
	}

	Quaternion rotation =  Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(0.0f),
		DirectX::XMConvertToRadians(-90.0f),
		DirectX::XMConvertToRadians(0.0f));

	m_pillar->SetLocalRotation(rotation);

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void RisingPillarRise::Exit()
{

}



