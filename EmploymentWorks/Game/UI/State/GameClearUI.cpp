/*
	@file	GameClearUI.cpp
	@brief	TPSカメラクラス
*/
#include "pch.h"
#include "Game/UI/State//GameClearUI.h"
#include "Game/Screen.h"
#include "Game/Object/Player/Player.h"
#include "Libraries/MyLib/Mouse.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Scene/PlayScene.h"

const int MAXANGLEY = 100;
const DirectX::SimpleMath::Vector3 TARGET = DirectX::SimpleMath::Vector3(0, 1, 0); //ステージの中心

const float MOVESPEED = 0.5f;




//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
GameClearUI::GameClearUI()
	:
	m_commonResources{},
	m_clearTime{}
{


}

void GameClearUI::Initialize(CommonResources* resources)
{
	m_commonResources = resources;


	CreateClearTex();

	m_clearTime = 0;

	m_changeResultScene = false;

	m_nextState = NextState::ReTry;

}

//-------------------------------------------------------------------
// 更新する
//-------------------------------------------------------------------
void GameClearUI::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;



	DirectX::SimpleMath::Vector2 scale = m_clearUI->GetScale();

	scale.x += 1.7f * elapsedTime;
	scale.y += 1.7f * elapsedTime;

	scale.x = std::min(scale.x,1.0f);
	scale.y = std::min(scale.y, 1.0f);

	m_clearUI->SetScale(scale);

	if (scale.x < 1)
	{
		return;
	}

	//背景が最大まで大きくなったら

	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	if (kbTracker->released.W)
	{
		m_nextState = NextState::ReTry;
		//大きさを戻す
		m_titleUI->SetScale(m_titleUI->GetBaseScale());
	}
	else if (kbTracker->released.S)
	{
		m_nextState = NextState::Title;
		//大きさを戻す
		m_reTryUI->SetScale(m_reTryUI->GetBaseScale());

	}

	if (kbTracker->released.Space)
	{
		switch (m_nextState)
		{
			case GameClearUI::NextState::ReTry:				
				m_playScene->SetNextSceneID(PlayScene::SceneID::PLAY);
				break;
			case GameClearUI::NextState::Title:
				m_playScene->SetNextSceneID(PlayScene::SceneID::TITLE);

				break;
			default:
				break;
		}
	}

	

	switch (m_nextState)
	{
		case GameClearUI::NextState::ReTry:

			scale = m_reTryUI->GetBaseScale();
			scale.x *= 1.4f;
			scale.y *= 1.4f;
			m_reTryUI->SetScale(scale);
			break;
		case GameClearUI::NextState::Title:
			scale = m_titleUI->GetBaseScale();
			scale.x *= 1.4f;
			scale.y *= 1.4f;
			m_titleUI->SetScale(scale);

			break;
		default:
			break;
	}

}

void GameClearUI::Render()
{

	m_clearUI->Render();

	m_reTryUI->Render();

	m_titleUI->Render();

}




void GameClearUI::Enter()
{
}


void GameClearUI::Exit()
{

}

void GameClearUI::RegistrationInformation(PlayScene* playScene)
{

	m_playScene = playScene;

}



/// <summary>
/// Claer画像の追加
/// </summary>
/// <param name="path"></param>
/// <param name="position"></param>
/// <param name="scale"></param>
/// <param name="anchor"></param>
/// <param name="kind"></param>
void GameClearUI::ClearTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
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

void GameClearUI::ReTryTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{

	m_reTryUI = std::make_unique<UserInterface>();
	//  指定された画像を表示するためのアイテムを作成する
	m_reTryUI->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	m_reTryUI->SetWindowSize(m_windowWidth, m_windowHeight);


}

void GameClearUI::TitleTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{

	m_titleUI = std::make_unique<UserInterface>();
	//  指定された画像を表示するためのアイテムを作成する
	m_titleUI->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	m_titleUI->SetWindowSize(m_windowWidth, m_windowHeight);


}



void GameClearUI::CreateClearTex()
{
	using namespace DirectX::SimpleMath;

	ClearTexAdd(L"Resources/Textures/ClearBackGraund.png"
		, Vector2(640, 360)
		, Vector2(1.0f, 1.0f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	ReTryTexAdd(L"Resources/Textures/ClearReTryTex.png"
		, Vector2(640, 360)
		, Vector2(1.0f, 1.0f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	TitleTexAdd(L"Resources/Textures/ClearTitleTex.png"
		, Vector2(640, 500)
		, Vector2(1.0f,1.0f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);


}



