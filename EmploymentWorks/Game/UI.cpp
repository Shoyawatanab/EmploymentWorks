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

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
UI::UI(Player* player, Enemy* enemy)
	:
	m_windowHeight(0)
	, m_windowWidth(0)
	, m_pDR(nullptr)
	,m_enemy{enemy}
	,m_player{player}
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
void UI::Initialize(DX::DeviceResources* pDR, int width, int height)
{
	using namespace DirectX::SimpleMath;
	assert(pDR);

	m_pDR = pDR;
	m_windowWidth = width;
	m_windowHeight = height;


	CreateEnemyHP();
	CreatePlayerHP();


	m_enemyHP[1]->SetRenderRatio(1.0f);

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

	for (int i = 0 ; i < m_player->GetPlayerHP();i++)
	{
		m_playerHP[i]->Render();

	}


}



void UI::EnemyHPAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{
	//  メニューとしてアイテムを追加する
	std::unique_ptr<UserInterface> userInterface = std::make_unique<UserInterface>();
	//  指定された画像を表示するためのアイテムを作成する
	userInterface->Create(m_pDR
		, path
		, position
		, scale
		, anchor
		,kind);

	userInterface->SetWindowSize(m_windowWidth, m_windowHeight);

	m_enemyHP.push_back(std::move(userInterface));

}

void UI::PlayerHPAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{

	//  メニューとしてアイテムを追加する
	std::unique_ptr<UserInterface> userInterface = std::make_unique<UserInterface>();
	//  指定された画像を表示するためのアイテムを作成する
	userInterface->Create(m_pDR
		, path
		, position
		, scale
		, anchor
		, kind);

	userInterface->SetWindowSize(m_windowWidth, m_windowHeight);

	m_playerHP.push_back(std::move(userInterface));



}

void UI::CreateEnemyHP()
{
	using namespace DirectX::SimpleMath;
	//  背景となるウィンドウ画像を読み込む

//  草画像を読み込む
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

