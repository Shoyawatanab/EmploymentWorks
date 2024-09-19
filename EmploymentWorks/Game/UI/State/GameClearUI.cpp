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

	m_lerpTime = 0;

}

//-------------------------------------------------------------------
// 更新する
//-------------------------------------------------------------------
void GameClearUI::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//float additive = 1.7f * elapsedTime;

	//背景を大きくする
	//DirectX::SimpleMath::Vector2 scale = m_clearUI->GetScale();

	//scale.x += additive;
	//scale.y += additive;

	//scale.x = std::min(scale.x,1.0f);
	//scale.y = std::min(scale.y, 1.0f);

	//m_clearUI->SetScale(scale);

	//scale = m_reTryUI->GetScale();

	//scale.x += additive;
	//scale.y += additive;

	//scale.x = std::min(scale.x, 1.0f);
	//scale.y = std::min(scale.y, 1.0f);

	//m_reTryUI->SetScale(scale);

	//scale = m_titleUI->GetScale();

	//scale.x += additive;
	//scale.y += additive;

	//scale.x = std::min(scale.x, 1.0f);
	//scale.y = std::min(scale.y, 1.0f);

	//m_titleUI->SetScale(scale);

	DirectX::SimpleMath::Vector2 Position;
	DirectX::SimpleMath::Vector2 Scale;


	//背景の座標
	Position = DirectX::SimpleMath::Vector2::Lerp(m_clearUI->GetStartPosition(),m_clearUI->GetEndPosition(),m_lerpTime);
	//背景の大きさ
	Scale = DirectX::SimpleMath::Vector2::Lerp(m_clearUI->GetStartScale(), m_clearUI->GetEndScale(), m_lerpTime);
	//値の代入
	m_clearUI->SetPosition(Position);
	m_clearUI->SetScale(Scale);

	//ReTry画像の座標
	Position = DirectX::SimpleMath::Vector2::Lerp(m_reTryUI->GetStartPosition(), m_reTryUI->GetEndPosition(), m_lerpTime);
	//ReTry画像の大きさ
	Scale = DirectX::SimpleMath::Vector2::Lerp(m_reTryUI->GetStartScale(), m_reTryUI->GetEndScale(), m_lerpTime);
	//値の代入
	m_reTryUI->SetPosition(Position);
	m_reTryUI->SetScale(Scale);

	//Title画像の座標
	Position = DirectX::SimpleMath::Vector2::Lerp(m_titleUI->GetStartPosition(), m_titleUI->GetEndPosition(), m_lerpTime);
	//title画像の大きさ
	Scale = DirectX::SimpleMath::Vector2::Lerp(m_titleUI->GetStartScale(), m_titleUI->GetEndScale(), m_lerpTime);
	//値の代入
	m_titleUI->SetPosition(Position);
	m_titleUI->SetScale(Scale);


	m_lerpTime += elapsedTime;


	m_lerpTime = std::min(m_lerpTime, 1.0f);


	if (m_lerpTime < 1)
	{
		return;
	}

	//背景が最大まで大きくなったら

	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	if (kbTracker->released.W)
	{
		m_nextState = NextState::ReTry;
		//大きさを戻す
		//m_titleUI->SetScale(m_titleUI->GetBaseScale());
	}
	else if (kbTracker->released.S)
	{
		m_nextState = NextState::Title;
		//大きさを戻す
		//m_reTryUI->SetScale(m_reTryUI->GetBaseScale());

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


	
	//選ばれている画像の大きさを少し大きくする
	switch (m_nextState)
	{
		case GameClearUI::NextState::ReTry:
			Scale = m_reTryUI->GetScale();
			Scale.x *= 1.3f;
			Scale.y *= 1.3f;

			m_reTryUI->SetScale(Scale);

			break;
		case GameClearUI::NextState::Title:
			Scale = m_titleUI->GetScale();
			Scale.x *= 1.3f;
			Scale.y *= 1.3f;

			m_titleUI->SetScale(Scale);

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

	m_lerpTime = 0;

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

	//終了時の座標の設定
	m_clearUI->SetEndPosition(DirectX::SimpleMath::Vector2(640,360));
	//終了時の大きさの設定
	m_clearUI->SetEndScale(DirectX::SimpleMath::Vector2::One);

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

	//終了時の座標の設定
	m_reTryUI->SetEndPosition(DirectX::SimpleMath::Vector2(640, 370));
	//終了時の大きさの設定
	m_reTryUI->SetEndScale(DirectX::SimpleMath::Vector2::One);

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
	//終了時の座標の設定
	m_titleUI->SetEndPosition(DirectX::SimpleMath::Vector2(640, 500));
	//終了時の大きさの設定
	m_titleUI->SetEndScale(DirectX::SimpleMath::Vector2::One);

}



void GameClearUI::CreateClearTex()
{
	using namespace DirectX::SimpleMath;

	ClearTexAdd(L"Resources/Textures/ClearBackGraund.png"
		, Vector2(640, 360)
		, Vector2(0.0f, 0.0f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	ReTryTexAdd(L"Resources/Textures/ClearReTryTex.png"
		, Vector2(640, 360)
		, Vector2(0.0f, 0.0f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	TitleTexAdd(L"Resources/Textures/ClearTitleTex.png"
		, Vector2(640, 360)
		, Vector2(0.0f,0.0f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);


}



