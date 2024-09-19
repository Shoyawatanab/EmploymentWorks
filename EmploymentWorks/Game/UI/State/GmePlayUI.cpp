/*
	@file	GamePlayUI.cpp
	@brief	TPSカメラクラス
*/
#include "pch.h"
#include "Game/UI/State/GmePlayUI.h"
#include "Game/Screen.h"
#include "Game/Object/Player/Player.h"
#include "Libraries/MyLib/Mouse.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"


const int MAXANGLEY = 100;
const DirectX::SimpleMath::Vector3 TARGET = DirectX::SimpleMath::Vector3(0, 1, 0); //ステージの中心

const float MOVESPEED = 0.5f;




//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
GamePlayUI::GamePlayUI()
	:
	m_commonResources{},
	m_windowWidth{},
	m_windowHeight{},
	m_player{},
	m_enemy{},
	m_playerHP{},
	m_enemyHP{}
{


}

void GamePlayUI::Initialize(CommonResources* resources)
{
	m_commonResources = resources;
	CreateEnemyHP();
	CreatePlayerHP();
	CreateBoomerang();

	//ボスHPの割合をセットする
	float EnemyHp = m_enemy->GetHp();
	float ratio = EnemyHp / m_enemy->GetMAXHp();
	m_enemyHP[1]->SetRenderRatio(ratio);


}

//-------------------------------------------------------------------
// 更新する
//-------------------------------------------------------------------
void GamePlayUI::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();

	//敵のHPの取得
	float EnemyHp = m_enemy->GetHp();
	//割合を求める
	float ratio = EnemyHp / m_enemy->GetMAXHp();
	//割合を代入
	m_enemyHP[1]->SetRenderRatio(ratio);

	//ブーメランのUIの座標を初期値に
	for (auto& boomerangUI : m_boomerangUI)
	{
		boomerangUI->SetPosition(boomerangUI->GetStartPosition());
	}



	//使用中のブーメランのIndexをもとにUIを
	//使用中のブーメランのIndexの取得
	int Index = m_player->GetUsingBoomerangIndex();
	//使用中のブーメランのの座標の取得
	DirectX::SimpleMath::Vector2 Pos = m_boomerangUI[Index]->GetStartPosition();
	//Y座標を上に
	Pos.y -= 20;
	//座標の代入
	m_boomerangUI[Index]->SetPosition(Pos);

	m_boomerangBackUI[0]->SetPosition(Pos);

}

void GamePlayUI::Render()
{

	for (auto& enemyHP : m_enemyHP)
	{
		enemyHP->Render();

	}



	for (int i = 0; i < m_player->GetPlayerHP(); i++)
	{
		m_playerHP[i]->Render();

	}

	for (auto& boomerangUI : m_boomerangUI)
	{
		boomerangUI->Render();
	}

	for (auto& boomerangBackUI : m_boomerangBackUI)
	{
		boomerangBackUI->Render();
	}



}




void GamePlayUI::Enter()
{

}


void GamePlayUI::Exit()
{

}

void GamePlayUI::RegistrationInformation(Player* player, Enemy* enemy)
{

	m_player = player;
	m_enemy = enemy;

}

void GamePlayUI::EnemyHPAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
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

void GamePlayUI::PlayerHPAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
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

void GamePlayUI::BoomerangAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
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

	m_boomerangUI.push_back(std::move(userInterface));

}

void GamePlayUI::BoomerangBackAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
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

	m_boomerangBackUI.push_back(std::move(userInterface));


}

void GamePlayUI::CreateEnemyHP()
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

void GamePlayUI::CreatePlayerHP()
{
	using namespace DirectX::SimpleMath;

	for (int i = 0; i < 3; i++)
	{
		//  草画像を読み込む
		PlayerHPAdd(L"Resources/Textures/HP.png"
			, Vector2(50 + 70 * static_cast<float>(i), 680)
			, Vector2(1.0f, 1.0f)
			, ANCHOR::MIDDLE_CENTER
			, UserInterface::Kinds::UI);

	}



}

void GamePlayUI::CreateBoomerang()
{

	using namespace DirectX::SimpleMath;

	for (int i = 0; i < 3; i++)
	{
		//  草画像を読み込む
		BoomerangAdd(L"Resources/Textures/BoomerangUI.png"
			, Vector2(50 + 70 * static_cast<float>(i), 610)
			, Vector2(0.1f, 0.1f)
			, ANCHOR::MIDDLE_CENTER
			, UserInterface::Kinds::UI);

	}


	//  草画像を読み込む
	BoomerangBackAdd(L"Resources/Textures/UIboomerangBack.png"
		, Vector2(50, 610)
		, Vector2(0.1f, 0.1f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);


}
