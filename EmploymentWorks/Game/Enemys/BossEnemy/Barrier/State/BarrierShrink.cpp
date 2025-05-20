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


/// <summary>
/// コンストラク
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="barrier">バリア</param>
BarrierShrink::BarrierShrink(CommonResources* resources
	, Barrier* barrier)
	:
	m_time{}
	,m_barrier{barrier}
{
	UNREFERENCED_PARAMETER(resources);

}



/// <summary>
/// デストラクタ
/// </summary>
BarrierShrink::~BarrierShrink()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void BarrierShrink::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);

}

void BarrierShrink::Update(const float& elapsedTime)
{

	using namespace DirectX::SimpleMath;

	float ratio = m_time / 0.35f;

	ratio = std::min(ratio, 1.0f);

	Vector3 scale = Vector3::Lerp(Barrier::SCALE,Vector3::Zero, ratio);

	m_barrier->SetLocalScale(scale);

	m_time += elapsedTime;

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BarrierShrink::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}

/// <summary>
/// 状態に入った時
/// </summary>
void BarrierShrink::Enter()
{

	m_time = 0;

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BarrierShrink::Exit()
{
}






