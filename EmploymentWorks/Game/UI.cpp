/*
	@file	UI.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "UI.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Object/Enemy/Enemy.h"
#include "Game/Object/Player/Player.h"
#include "Game/Scene/PlayScene.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
UI::UI(PlayScene* playScene, Player* player, Enemy* enemy)
	:
	m_windowHeight(0)
	, m_windowWidth(0)
	, m_commonResources{}
	, m_enemy{ enemy }
	, m_player{ player }
	, m_clearUI{}
	, m_playScene{ playScene }
	, m_clearTime{}

{
	m_enemyHP.clear();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
UI::~UI()
{
	// do nothing.


}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void UI::Initialize(CommonResources* resources, int width, int height)
{
	using namespace DirectX::SimpleMath;
	assert(resources);

	m_commonResources = resources;
	m_windowWidth = width;
	m_windowHeight = height;


	CreateEnemyHP();
	CreatePlayerHP();
	CreateClearTex();
	CreateGameOverTex();

	//ボスHPの割合をセットする
	float EnemyHp = m_enemy->GetHp();
	float ratio = EnemyHp / m_enemy->GetMAXHp();
	m_enemyHP[1]->SetRenderRatio(ratio);

	//背景の透明度を０に設定
	m_gameOverUI->SetAlphaValue(0.0f);
	//リトライ画像の透明度を０に設定
	m_gameOverReTryUI->SetAlphaValue(-0.3f);
	//やめる画像の透明度を０に設定
	m_gameOverEndUI->SetAlphaValue(-0.3f);
	//矢印画像の透明度の設定
	m_gameOverArrowUI->SetAlphaValue(-0.3f);

	m_clearTime = 0;

	m_changeResultScene = false;


}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void UI::Update(float elapsedTime)
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	UNREFERENCED_PARAMETER(elapsedTime);

	float EnemyHp = m_enemy->GetHp();


	float ratio = EnemyHp / m_enemy->GetMAXHp();

	//ratio = 0.5f;

	m_enemyHP[1]->SetRenderRatio(ratio);


}

void UI::GameClearUpdate(float elapsedTime)
{

	DirectX::SimpleMath::Vector2 pos = m_clearUI->GetPosition();

	pos.y += 200.0f * elapsedTime;

	pos.y = std::min(pos.y, 360.0f);

	m_clearUI->SetPosition(pos);

	if (pos.y <= 360)
	{

		//クリアの画像が中心に来てからの時間の計測
		m_clearTime += elapsedTime;

	}

	if (m_clearTime >= 3)
	{
		m_changeResultScene = true;
	}

}


void UI::GameOverUpdate(float elapsedTime)
{




	//加算値を求める
	float Additive = 0.5f * elapsedTime;



	//背景の透明度の変更
	float alpha;
	alpha = m_gameOverUI->GetAlphaValue();
	//透明度を加算
	alpha += Additive;
	//透明度をセット
	m_gameOverUI->SetAlphaValue(alpha);


	//リトライ画像の透明度の取得
	alpha = m_gameOverReTryUI->GetAlphaValue();
	//透明度を加算
	alpha += Additive;
	//透明度をセット
	m_gameOverReTryUI->SetAlphaValue(alpha);


	//やめる画像の透明度の取得
	alpha = m_gameOverEndUI->GetAlphaValue();
	//透明度を加算
	alpha += Additive;
	//透明度をセット
	m_gameOverEndUI->SetAlphaValue(alpha);

	// キーボードステートトラッカーを取得する
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	if (kbTracker->released.W)
	{

		m_gameOverArrowUI->SetPosition(DirectX::SimpleMath::Vector2(500, 420));

	}
	else if (kbTracker->released.S)
	{

		m_gameOverArrowUI->SetPosition(DirectX::SimpleMath::Vector2(500, 510));


	}

	if (kbTracker->released.Space)
	{

		//リトライなら
		if (m_gameOverArrowUI->GetPosition().y <= 420)
		{

			m_playScene->SetNextSceneID(PlayScene::SceneID::PLAY);

		}
		else
		{
			//やめる
			PostQuitMessage(0);
		}

	}

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void UI::Render()
{
	using namespace DirectX::SimpleMath;

	for (auto& enemyHP : m_enemyHP)
	{
		enemyHP->Render();

	}



	for (int i = 0; i < m_player->GetPlayerHP(); i++)
	{
		m_playerHP[i]->Render();

	}




}

/// <summary>
/// クリアやゲームオーバーのテキスト表示関数
/// </summary>
void UI::ClearTexRender()
{

	m_clearUI->Render();

}

void UI::GameOverRender()
{

	m_gameOverUI->Render();

	m_gameOverReTryUI->Render();

	m_gameOverEndUI->Render();

	m_gameOverArrowUI->Render();


}



void UI::EnemyHPAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{
	//  メニューとしてアイテムを追加する
	std::unique_ptr<UserInterface> userInterface = std::make_unique<UserInterface>();
	//  指定された画像を表示するためのアイテムを作成する
	userInterface->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	userInterface->SetWindowSize(m_windowWidth, m_windowHeight);

	m_enemyHP.push_back(std::move(userInterface));

}

void UI::PlayerHPAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{

	//  メニューとしてアイテムを追加する
	std::unique_ptr<UserInterface> userInterface = std::make_unique<UserInterface>();
	//  指定された画像を表示するためのアイテムを作成する
	userInterface->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	userInterface->SetWindowSize(m_windowWidth, m_windowHeight);

	m_playerHP.push_back(std::move(userInterface));

}

/// <summary>
/// Claer画像の追加
/// </summary>
/// <param name="path"></param>
/// <param name="position"></param>
/// <param name="scale"></param>
/// <param name="anchor"></param>
/// <param name="kind"></param>
void UI::ClearTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{

	m_clearUI = std::make_unique<UserInterface>();
	//  指定された画像を表示するためのアイテムを作成する
	m_clearUI->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	m_clearUI->SetWindowSize(m_windowWidth, m_windowHeight);


}

void UI::GameOverTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{

	m_gameOverUI = std::make_unique<UserInterface>();
	//  指定された画像を表示するためのアイテムを作成する
	m_gameOverUI->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	m_gameOverUI->SetWindowSize(m_windowWidth, m_windowHeight);


}

void UI::GameOverReTryTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{

	m_gameOverReTryUI = std::make_unique<UserInterface>();
	//  指定された画像を表示するためのアイテムを作成する
	m_gameOverReTryUI->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	m_gameOverReTryUI->SetWindowSize(m_windowWidth, m_windowHeight);


}

void UI::GameOverEndTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{

	m_gameOverEndUI = std::make_unique<UserInterface>();
	//  指定された画像を表示するためのアイテムを作成する
	m_gameOverEndUI->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	m_gameOverEndUI->SetWindowSize(m_windowWidth, m_windowHeight);


}

void UI::GameOverArrowTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{

	m_gameOverArrowUI = std::make_unique<UserInterface>();
	//  指定された画像を表示するためのアイテムを作成する
	m_gameOverArrowUI->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	m_gameOverArrowUI->SetWindowSize(m_windowWidth, m_windowHeight);


}

void UI::CreateEnemyHP()
{
	using namespace DirectX::SimpleMath;
	//  背景となるウィンドウ画像を読み込む

	EnemyHPAdd(L"Resources/Textures/BossHPBase.png"
		, Vector2(640, 50)
		, Vector2(0.9f, 0.5f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	EnemyHPAdd(L"Resources/Textures/EnemyHP.png"
		, Vector2(640, 50)
		, Vector2(0.91f, 0.39f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	EnemyHPAdd(L"Resources/Textures/EnemyName.png"
		, Vector2(640, 25)
		, Vector2(0.3f, 0.3f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);


}

void UI::CreatePlayerHP()
{
	using namespace DirectX::SimpleMath;

	for (int i = 0; i < 3; i++)
	{
		//  草画像を読み込む
		PlayerHPAdd(L"Resources/Textures/HP.png"
			, Vector2(50 + 70 * i, 680)
			, Vector2(1.0f, 1.0f)
			, ANCHOR::MIDDLE_CENTER
			, UserInterface::Kinds::UI);

	}


}

void UI::CreateClearTex()
{
	using namespace DirectX::SimpleMath;

	ClearTexAdd(L"Resources/Textures/GameClear.png"
		, Vector2(640, -50)
		, Vector2(0.5f, 0.5f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

}

void UI::CreateGameOverTex()
{

	using namespace DirectX::SimpleMath;

	GameOverTexAdd(L"Resources/Textures/GameOver.png"
		, Vector2(640, 360)
		, Vector2(1.0f, 1.0f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	GameOverReTryTexAdd(L"Resources/Textures/ReTry.png"
		, Vector2(640, 420)
		, Vector2(0.3f, 0.3f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	GameOverEndTexAdd(L"Resources/Textures/End.png"
		, Vector2(640, 510)
		, Vector2(0.3f, 0.3f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	GameOverArrowTexAdd(L"Resources/Textures/Arrow.png"
		, Vector2(500, 420)
		, Vector2(0.18f, 0.18f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	//上　420　　　下 510

}

