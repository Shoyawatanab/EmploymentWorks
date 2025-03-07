/*
	@file	UIManager.cpp
	@brief	
*/
#include "pch.h"
#include "UIManager.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include <cassert>
#include "Game/UI/State/UIStateMachine.h"
#include "Game/Observer/Messenger.h"

/// <summary>
/// コンストラクタ
/// </summary>
UIManager::UIManager()
	:
	m_commonResources{}
	,m_stateMahine{}
{
	m_stateMahine = std::make_unique<UIStateMachine>();
}


/// <summary>
/// デストラクタ
/// </summary>
UIManager::~UIManager()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void UIManager::Initialize(CommonResources* resources)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;

	m_stateMahine->Initialize(m_commonResources, m_stateMahine->GetGamePlayUI());

	Messenger::Attach(EventParams::EventType::GameClear, this);
	Messenger::Attach(EventParams::EventType::GameOver, this);

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void UIManager::Update(const float& elapsedTime)
{

	m_stateMahine->Update(elapsedTime);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void UIManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	using namespace DirectX::SimpleMath;

	m_stateMahine->Render(view, projection);

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void UIManager::Finalize()
{
	// do nothing.
}

/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="player">プレイヤ</param>
/// <param name="playScene">プレイシーン</param>
/// <param name="enemyManager">エネミーマネージャー</param>
void UIManager::AddPointer(Player* player, PlayScene* playScene, EnemyManager* enemyManager)
{

	m_stateMahine->AddPointer(player,playScene,enemyManager);

}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">イベントの種類</param>
/// <param name="datas">イベントのデータ</param>
void UIManager::Notify(EventParams::EventType type, void* datas)
{
	switch (type)
	{
		case EventParams::EventType::GameClear:
			m_stateMahine->ChangeState(m_stateMahine->GetGameEndUI());
			m_stateMahine->GetGameEndUI()->SetBackGraund(true);
			break;
		case EventParams::EventType::GameOver:
			m_stateMahine->ChangeState(m_stateMahine->GetGameEndUI());
			m_stateMahine->GetGameEndUI()->SetBackGraund(false);

			break;
		default:
			break;
	}
}




