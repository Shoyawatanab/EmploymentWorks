/*
	@file	BarrierShrink.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BarrierShrink.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Libraries/WataLib/Bounding.h"
#include "Game/Params.h"
#include "Game/Observer/Messenger.h"

#include "Game/Enemys/BossEnemy/Barrier/Barrier.h"
#include "Game/Enemys/BossEnemy/Barrier/State/BarrierStateMachine.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="parent">親</param>
BarrierShrink::BarrierShrink(CommonResources* resources
	, Barrier* barrier)
	:
	m_time{}
	,m_barrier{barrier}
{
}



/// <summary>
/// デストラクタ
/// </summary>
BarrierShrink::~BarrierShrink()
{
	// do nothing.
}

void BarrierShrink::Initialize(CommonResources* resources)
{
}

void BarrierShrink::Update(const float& elapsedTime)
{

	float ratio = m_time / 0.35f;

	ratio = std::min(ratio, 1.0f);

	Vector3 scale = Vector3::Lerp(Barrier::SCALE,Vector3::Zero, ratio);

	m_barrier->SetLocalScale(scale);

	m_time += elapsedTime;

}

void BarrierShrink::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
}

void BarrierShrink::Enter()
{



}

void BarrierShrink::Exit()
{
}






