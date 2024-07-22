/*
	@file	EnemyHP.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "EnemyHP.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Object/Enemy/Enemy.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
EnemyHP::EnemyHP( Enemy* enemy)
	:
	m_windowHeight(0)
	, m_windowWidth(0)
	, m_pDR(nullptr)
	,m_enemy{enemy}
	,m_enemyMaxHP{}
{
	m_userInterface.clear();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
EnemyHP::~EnemyHP()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void EnemyHP::Initialize(DX::DeviceResources* pDR, int width, int height)
{
	using namespace DirectX::SimpleMath;
	assert(pDR);

	m_pDR = pDR;
	m_windowWidth = width;
	m_windowHeight = height;

	//  背景となるウィンドウ画像を読み込む

	//  草画像を読み込む
	Add(L"Resources/Textures/BossHPBase.png"
		,Vector2(640, 50)
		,Vector2(0.9f, 0.5f)
		,ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	Add(L"Resources/Textures/EnemyHP.png"
		, Vector2(640, 50)
		, Vector2(0.91f, 0.39f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UIHP);

	Add(L"Resources/Textures/EnemyName.png"
		, Vector2(640, 25)
		, Vector2(0.3f, 0.3f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);



	m_userInterface[1]->SetRenderRatio(1.0f);
	m_enemyMaxHP = m_enemy->GetMAXHp();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void EnemyHP::Update(float elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	UNREFERENCED_PARAMETER(elapsedTime);


	float EnemyHp = m_enemy->GetHp();


	float ratio = EnemyHp / m_enemyMaxHP;
	m_userInterface[1]->SetRenderRatio(ratio);


}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void EnemyHP::Render()
{
	using namespace DirectX::SimpleMath;

	for (int i = 0; i < m_userInterface.size(); i++)
	{
		m_userInterface[i]->Render();

	}


}


void EnemyHP::Add(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
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

	//  アイテムを新しく追加
	m_userInterface.push_back(std::move(userInterface));





}

