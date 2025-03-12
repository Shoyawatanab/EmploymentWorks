/*
	@file	StageSelectScene.cpp
	@brief	タイトルシーンクラス
*/
#include "pch.h"
#include "StageSelectScene.h"
#include "Game/Screen.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>

#include "Libraries/WataLib/Fade.h"
#include "Libraries/WataLib/DrawTexture.h"
#include "Game/Params.h"
#include "Libraries/WataLib/DetectionCollision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
StageSelectScene::StageSelectScene(SceneManager* sceneManager)
	:
	m_commonResources{},
	m_isChangeScene{}
	,m_sceneManager{sceneManager}
	, m_buttom{}
	, m_selectButtomId{}

{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
StageSelectScene::~StageSelectScene()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void StageSelectScene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();


	auto buttom = std::make_unique<WataLib::DrawTexture>();
	buttom->Initialize(m_commonResources, L"Resources/Textures/Tutorial.png", DirectX::SimpleMath::Vector2(400, 360), Vector2(1.3f, 1.3f));

	m_buttom[0] = std::move(buttom);

	buttom = std::make_unique<WataLib::DrawTexture>();
	buttom->Initialize(m_commonResources, L"Resources/Textures/Stage1.png", DirectX::SimpleMath::Vector2(880, 360), Vector2(1.3f, 1.3f));

	m_buttom[1] = std::move(buttom);

	auto texture = std::make_unique<WataLib::DrawTexture>();
	texture->Initialize(m_commonResources, L"Resources/Textures/BackGraund.png", Vector2(Screen::CENTER_X,Screen::CENTER_Y), Vector2(0.4f, 0.4f));

	m_textures.push_back(std::move(texture));

	m_sceneManager->SetStageID(SceneManager::Stage1);



	// シーン変更フラグを初期化する
	m_isChangeScene = false;


	//フェードアウトの開始
	m_commonResources->GetFade()->StartNormalFadeOut();

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void StageSelectScene::Update(float elapsedTime)
{
	// 宣言をしたが、実際は使用していない変数
	UNREFERENCED_PARAMETER(elapsedTime);

	// キーボードステートトラッカーを取得する
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	const auto& state = m_commonResources->GetInputManager()->GetMouseState();

	const auto& tracker = m_commonResources->GetInputManager()->GetMouseTracker();

	Vector2 mousePosition = Vector2(state.x, state.y);

	//初期化
	m_selectButtomId = BUTTOM_INIAL_ID;

	for (auto& buttom : m_buttom)
	{
		buttom.second->SetScale(buttom.second->GetInialScale());
		if (WataLib::DetectionCollision::Circle_RectCheckHit(mousePosition, Params::MOUSE_RADIUS,
			buttom.second->GetPosition(), buttom.second->GetWidth(), buttom.second->GetHeight()))
		{
			buttom.second->SetScale(buttom.second->GetInialScale() * 1.4f);

			m_selectButtomId = buttom.first;

			break;

		}

	}



	//
	if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		if (m_selectButtomId != BUTTOM_INIAL_ID)
		{
			m_isChangeScene = true;

			switch (m_selectButtomId)
			{
				case 0:
					m_sceneManager->SetStageID(SceneManager::Stage1);
					break;
				case 1:
					m_sceneManager->SetStageID(SceneManager::Stage2);
					break;
				default:
					break;
			}

		}

	}

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void StageSelectScene::Render()
{
	auto states = m_commonResources->GetCommonStates();


	for (auto& texture : m_textures)
	{
		texture->Render();
	}

	for (auto& buttom : m_buttom)
	{
		buttom.second->Render();
	}


}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void StageSelectScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// 次のシーンIDを取得する
//---------------------------------------------------------
IScene::SceneID StageSelectScene::GetNextSceneID() const
{
	// シーン変更がある場合
	if (m_isChangeScene)
	{
		if (m_commonResources->GetFade()->GetFadeState() == Fade::FadeState::None)
		{
			m_commonResources->GetFade()->StartNormalFadeIn();

		}

		return IScene::SceneID::PLAY;
	}

	// シーン変更がない場合
	return IScene::SceneID::NONE;
}
