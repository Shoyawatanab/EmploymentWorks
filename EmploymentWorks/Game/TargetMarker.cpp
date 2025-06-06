/*
	@file	TargetMarker.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "TargetMarker.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "GameBase/Screen.h"
#include "Game/Observer/Messenger.h"
#include "Libraries/WataLib/UserInterface.h"
#include "Game/InstanceRegistry.h"

/// <summary>
/// コンストラクタ
/// </summary>
TargetMarker::TargetMarker()
	:
	m_commonResources{}
	,m_tpsCamera{ }
	, m_isTargetMarker{ false }
	,m_windowSize{}
	,m_marker{}
	,m_targetObject{}
	, m_isLockOn{false}
{

	InstanceRegistry::GetInstance()->Register<TargetMarker>("TargetMarker", this);

}

/// <summary>
/// デストラクタ
/// </summary>
TargetMarker::~TargetMarker()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void TargetMarker::Initialize(CommonResources* resources)
{
	using namespace DirectX::SimpleMath;

	m_commonResources = resources;

	m_tpsCamera = InstanceRegistry::GetInstance()->GetRegistryInstance<WataLib::TPS_Camera>("TPS_Camera");

	//画面サイズの取得
	m_windowSize.first = m_commonResources->GetDeviceResources()->GetOutputSize().right;
	m_windowSize.second = m_commonResources->GetDeviceResources()->GetOutputSize().bottom;


	m_isTargetMarker = false;

	m_marker = std::make_unique<UserInterface>();
	m_marker->Create(m_commonResources, "TargetMarker"
		,Vector2(200,200), Vector2(0.3f,0.3f));
	

	Messenger::GetInstance()->Rigister(GamePlayMessageType::BOOMERANG_GET_READY, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::BOOMERANG_GET_READY_END, this);

}


/// <summary>
/// 範囲内のオブジェクトを探す
/// </summary>
/// <param name="points">座標の配列</param>
/// <param name="center">中心座標</param>
/// <param name="range">半径</param>
/// <returns>範囲内の座標</returns>
DirectX::SimpleMath::Vector2 TargetMarker::FilterWithinRange(const std::vector<DirectX::SimpleMath::Vector3>& points, const DirectX::SimpleMath::Vector2& center, float range)
{

	using namespace DirectX::SimpleMath;
	//変数宣言
	DirectX::SimpleMath::Vector2 result;

	//画面の横のサイズを初期値とする
	float minLength = static_cast<float>(m_windowSize.first);

	m_isLockOn = false;

	//
	for (const auto& point : points)
	{
	}

	return result;

}


/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void TargetMarker::Update(float elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	UNREFERENCED_PARAMETER(elapsedTime);

	m_target = Vector3::Zero;

	//ブーメランを構えていないなら
	if (!m_isTargetMarker)
	{
		return;
	}

	std::vector<DirectX::SimpleMath::Vector3> positions;

	for (auto& object : m_targetObject)
	{
		if(object->GetIsEntityActive())
		{
			positions.push_back(object->GetPosition());

		}

	}

	DirectX::SimpleMath::Vector2 center = Vector2(Screen::CENTER_X, Screen::CENTER_Y);

	DirectX::SimpleMath::Vector2 result = FilterWithinRange(positions, center, RANGE);


	m_marker->SetPosition(result);


}

/// <summary>
/// 描画
/// </summary>
void TargetMarker::Render()
{
	using namespace DirectX::SimpleMath;


	if (m_isLockOn && m_isTargetMarker)
	{
		m_marker->Render();

	}


}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">イベントの種類</param>
/// <param name="datas">イベントのデータ</param>
void TargetMarker::Notify(const Telegram<GamePlayMessageType>& telegram)
{

	switch (telegram.messageType)
	{
		case ::GamePlayMessageType::BOOMERANG_GET_READY:
			m_isTargetMarker = true;
			break;
		case ::GamePlayMessageType::BOOMERANG_GET_READY_END:
			m_isTargetMarker = false;
			m_isLockOn = false;

			break;
		default:
			break;
	}

}

/// <summary>
/// ワールド座標をスクリーン座標に変換
/// </summary>
/// <param name="worldPos">ワールド座標</param>
/// <param name="worldMatrix">ワールドの行列</param>
/// <param name="viewMatrix"></param>
/// <param name="projectionMatrix"></param>
/// <param name="screenWidth"></param>
/// <param name="screenHeight"></param>
/// <returns></returns>
DirectX::SimpleMath::Vector2 TargetMarker::WorldToScreen(const DirectX::SimpleMath::Vector3& worldPos,
	const DirectX::SimpleMath::Matrix& worldMatrix,
	const DirectX::SimpleMath::Matrix& viewMatrix,
	const DirectX::SimpleMath::Matrix& projectionMatrix,
	int screenWidth, int screenHeight)
{
	using namespace DirectX::SimpleMath;
	// ワールド座標を変換するための行列を結合
	Matrix transformMatrix = worldMatrix * viewMatrix * projectionMatrix;

	// ワールド座標をプロジェクション空間に変換
	Vector3 projectedPos = Vector3::Transform(worldPos, transformMatrix);

	// 射影された座標をスクリーン座標に変換
	float x = (projectedPos.x / projectedPos.z * 0.5f + 0.5f) * screenWidth;
	float y = (0.5f - projectedPos.y / projectedPos.z * 0.5f) * screenHeight;

	return Vector2(x, y);

}







