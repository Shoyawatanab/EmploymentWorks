/*
	@file	GameOverUI.cpp
	@brief	TPSカメラクラス
*/
#include "pch.h"
#include "Game/UI/State/GameOverUI.h"
#include "Game/Screen.h"
#include "Game/Object/Player/Player.h"
#include "Libraries/MyLib/Mouse.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Game/Scene/PlayScene.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"


const int MAXANGLEY = 100;
const DirectX::SimpleMath::Vector3 TARGET = DirectX::SimpleMath::Vector3(0, 1, 0); //ステージの中心

const float MOVESPEED = 0.5f;




//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
GameOverUI::GameOverUI()
	
{


}

void GameOverUI::Initialize(CommonResources* resources)
{

	m_commonResources = resources;

	CreateGameOverTex();


	//背景の透明度を０に設定
	m_gameOverUI->SetAlphaValue(0.0f);
	//リトライ画像の透明度を０に設定
	m_gameOverReTryUI->SetAlphaValue(-0.3f);
	//やめる画像の透明度を０に設定
	m_gameOverEndUI->SetAlphaValue(-0.3f);

	m_nextState = NextState::ReTry;


}

//-------------------------------------------------------------------
// 更新する
//-------------------------------------------------------------------
void GameOverUI::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();


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

	if (alpha < 1)
	{
		return;
	}

	if (kbTracker->released.W)
	{

		m_nextState = NextState::ReTry;
		//大きさを戻す
		m_gameOverEndUI->SetScale(m_gameOverEndUI->GetBaseScale());

	}
	else if (kbTracker->released.S)
	{

		m_nextState = NextState::End;
		m_gameOverReTryUI->SetScale(m_gameOverReTryUI->GetBaseScale());

	}

	if (kbTracker->released.Space)
	{
		switch (m_nextState)
		{
			case GameOverUI::NextState::ReTry:
				m_playScene->SetNextSceneID(PlayScene::SceneID::PLAY);
				break;
			case GameOverUI::NextState::End:
				
				PostQuitMessage(0);

				break;
			default:
				break;
		}

	}


	DirectX::SimpleMath::Vector2 scale = DirectX::SimpleMath::Vector2::Zero;


	switch (m_nextState)
	{
		case GameOverUI::NextState::ReTry:			
			scale = m_gameOverReTryUI->GetBaseScale();
			scale.x *= 1.4f;
			scale.y *= 1.4f;
			m_gameOverReTryUI->SetScale(scale);
			break;
		case GameOverUI::NextState::End:
			scale = m_gameOverEndUI->GetBaseScale();
			scale.x *= 1.4f;
			scale.y *= 1.4f;
			m_gameOverEndUI->SetScale(scale);

			break;
		default:
			break;
	}

}

void GameOverUI::Render()
{

	m_gameOverUI->Render();

	m_gameOverReTryUI->Render();

	m_gameOverEndUI->Render();




}




void GameOverUI::Enter()
{
}


void GameOverUI::Exit()
{

}

void GameOverUI::RegistrationInformation(PlayScene* playScene)
{

	m_playScene = playScene;

}


void GameOverUI::GameOverTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
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

void GameOverUI::GameOverReTryTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
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

void GameOverUI::GameOverEndTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
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

void GameOverUI::CreateGameOverTex()
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


	//上　420　　　下 510

}

