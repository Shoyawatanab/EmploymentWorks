/*
	@file	BarrierGenerate.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BarrierGenerate.h"
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
BarrierGenerate::BarrierGenerate(CommonResources* resources
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
BarrierGenerate::~BarrierGenerate()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void BarrierGenerate::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BarrierGenerate::Update(const float& elapsedTime)
{

	float ratio = m_time / 0.35f;

	ratio = std::min(ratio, 1.0f);

	Vector3 scale = Vector3::Lerp(Vector3::Zero, Barrier::SCALE, ratio);

	m_barrier->SetLocalScale(scale);

	m_time += elapsedTime;

}

/// <summary>
/// 状態に入った時
/// </summary>
void BarrierGenerate::Enter()
{

	Quaternion rotation = Quaternion::CreateFromAxisAngle(
		Vector3::UnitY, DirectX::XMConvertToRadians(45.0f));

	m_barrier->SetLocalRotation(rotation);

	m_barrier->SetLocalPosition(Vector3(3.5f, 0, 2));
	m_barrier->SetLocalScale(Vector3::Zero);

	m_time = 0;

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BarrierGenerate::Exit()
{
}






