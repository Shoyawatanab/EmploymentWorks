#include "pch.h"
#include "GameEndUI.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"
#include "Game/Scene/PlayScene.h"
#include "Libraries/WataLib/UserInterface.h"
#include "Game/InstanceRegistry.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameEndUI::GameEndUI()
	:
	m_commonResources{}
	,m_position{}
	,m_scale{}
	,m_rotation{}
	,m_player{}
	,m_windowSize{}
	, m_clearBackGraund{}
	,m_overBackGraund{}
	,m_titleUI{}
	, m_reTryUI{}
	,m_animationTime{}
	,m_state{}
	,m_backGraund{}
	,m_enemyAnimationTime{}
	,m_playScene{}
{

	m_clearBackGraund = std::make_unique<UserInterface>();
	m_overBackGraund = std::make_unique<UserInterface>();
	m_titleUI = std::make_unique<UserInterface>();
	m_reTryUI = std::make_unique<UserInterface>();

}

/// <summary>
/// デストラクタ
/// </summary>
GameEndUI::~GameEndUI()
{
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void GameEndUI::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

	//描画
	m_backGraund->Render();
	m_titleUI->Render();
	m_reTryUI->Render();

	//アニメーションが終われば
	if (m_animationTime < MAXANIMATIONTIME)
	{
		return;
	}

	//画像の描画
	for (auto& texture : m_textures)
	{
		texture->Render();
	}

	m_arrow->Render();

	
}


/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="player">プレイヤ</param>
/// <param name="playScene">プレイシーン</param>
void GameEndUI::AddPointer(PlayScene* playScene)
{
	m_playScene = playScene;
}

/// <summary>
/// 画像の作成
/// </summary>
void GameEndUI::CreateTexture()
{

	m_clearBackGraund->Create(
		m_commonResources, "ClearBackGraund"
		, CENTERPOSITION, Vector2::Zero
	);	
	m_overBackGraund->Create(
		m_commonResources, "GameOver"
		, CENTERPOSITION, Vector2::Zero
	);
	m_titleUI->Create(
		m_commonResources, "ClearTitleTex"
		, CENTERPOSITION, Vector2::Zero
	);

	m_reTryUI->Create(
		m_commonResources, "ClearReTryTex"
		, CENTERPOSITION, Vector2::Zero
	);

}

/// <summary>
/// ポップアップアニメーション
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void GameEndUI::Animation(const float& elapsedTime)
{
	//割合を求める
	float ratio = m_animationTime / MAXANIMATIONTIME;

	ratio = std::min(ratio, 1.0f);

	Vector2 position;
	Vector2 scale;
	//大きさを求める
	scale = Vector2::Lerp(Vector2::Zero, ENDSCSLE, ratio);
	m_backGraund->SetScale(scale);
	m_titleUI->SetScale(scale);
	m_reTryUI->SetScale(scale);

	//背景
	position = Vector2::Lerp(CENTERPOSITION, BACKGRAUNDENDPOSITION, ratio);
	m_backGraund->SetPosition(position);
	//タイトルUI
	position = Vector2::Lerp(CENTERPOSITION, TITLEUIENDPOSITION, ratio);
	m_titleUI->SetPosition(position);
	//リトライUI
	position = Vector2::Lerp(CENTERPOSITION, RETRYUIENDPOSITION, ratio);
	m_reTryUI->SetPosition(position);

	m_animationTime += elapsedTime;

}



/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void GameEndUI::Initialize(CommonResources* resources)
{
	m_commonResources = resources;

	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

	//画面サイズの取得
	m_windowSize.first = m_commonResources->GetDeviceResources()->GetOutputSize().right;
	m_windowSize.second = m_commonResources->GetDeviceResources()->GetOutputSize().bottom;

	CreateTexture();

	m_state = State::RETRY;

	m_backGraund = m_clearBackGraund.get();


	auto texture = std::make_unique<UserInterface>();
	texture->Create(
		m_commonResources, "ChangeUI", CHANGEUI_POSITION, CHANGEUI_SCALE
	);

	m_textures.push_back(std::move(texture));


	texture = std::make_unique<UserInterface>();
	texture->Create(
		m_commonResources, "DecisionUI", DECISIONUI_POSITION, DECISIONUI_SCALE
	);

	m_textures.push_back(std::move(texture));


	m_arrow = std::make_unique<UserInterface>();

	m_arrow->Create(
		m_commonResources, "Arrow", ARROW_UP_POSITION, ARROW_SCALE);



}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void GameEndUI::Update(const float& elapsedTime)
{

	//UIができるまでの時間
	if (m_enemyAnimationTime < ENEMYANIMATIONTIME)
	{
		m_enemyAnimationTime += elapsedTime;
		return;
	}

	//アニメーション
	Animation(elapsedTime);

	if (m_animationTime < MAXANIMATIONTIME)
	{
		return;
	}
	
	// キーボードステートトラッカーを取得する
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	if (kbTracker->released.W)
	{
		m_state = State::RETRY;
		m_arrow->SetPosition(ARROW_UP_POSITION);

	}
	else if (kbTracker->released.S)
	{
		m_state = State::TITLE;
		m_arrow->SetPosition(ARROW_DOWN_POSITION2);
	}

	//UIの大きさをStateに応じて変更
	switch (m_state)
	{
		case GameEndUI::State::TITLE:
			m_reTryUI->SetScale(m_reTryUI->GetInialScale());
			m_titleUI->SetScale(m_titleUI->GetInialScale() * EXPANSION);

			break;
		case GameEndUI::State::RETRY:
			m_reTryUI->SetScale(m_reTryUI->GetInialScale() * EXPANSION);
			m_titleUI->SetScale(m_titleUI->GetInialScale());

			break;
		default:
			break;
	}

	//次に遷移
	if (kbTracker->released.Space)
	{
		switch (m_state)
		{
			case GameEndUI::State::TITLE:
				m_playScene->SetNextSceneID(PlayScene::SceneID::TITLE);
				break;
			case GameEndUI::State::RETRY:
				m_playScene->SetNextSceneID(PlayScene::SceneID::PLAY);
				break;
			default:
				break;
		}


	}

}

/// <summary>
/// 状態に入った時
/// </summary>
void GameEndUI::Enter()
{



}

/// <summary>
/// 状態を抜けた時
/// </summary>
void GameEndUI::Exit()
{
}




