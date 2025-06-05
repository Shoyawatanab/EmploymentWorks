/*
	@file	StageSelectScene.cpp
	@brief	タイトルシーンクラス
*/
#include "pch.h"
#include "StageSelectScene.h"
#include "GameBase/Screen.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>

#include "Libraries/WataLib/Fade.h"
#include "Game/Params.h"
#include "Libraries/WataLib/DetectionCollision.h"
#include "Libraries/MyLib/DebugString.h"

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
void StageSelectScene::Initialize()
{
	m_commonResources = CommonResources::GetInstance();


	auto buttom = std::make_unique<UserInterface>();

	buttom->Create(m_commonResources, "Tutorial", DirectX::SimpleMath::Vector2(400, 360), Vector2(1.3f, 1.3f));

	m_buttom[0] = std::move(buttom);

	buttom = std::make_unique<UserInterface>();

	buttom->Create(m_commonResources, "Stage1", DirectX::SimpleMath::Vector2(880, 360), Vector2(1.3f, 1.3f));

	m_buttom[1] = std::move(buttom);

	auto texture = std::make_unique<UserInterface>();

	texture->Create(m_commonResources, "BackGraund", Vector2(Screen::CENTER_X, Screen::CENTER_Y), Vector2(0.4f, 0.4f));

	m_textures.push_back(std::move(texture));

	m_sceneManager->SetStageID(SceneManager::STAGE1);

	// シーン変更フラグを初期化する
	m_isChangeScene = false;

	//フェードアウトの開始
	m_commonResources->GetFade()->StartNormalFadeOut();

	ShowCursor(true);

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void StageSelectScene::SceneUpdate(float elapsedTime)
{
	// 宣言をしたが、実際は使用していない変数
	UNREFERENCED_PARAMETER(elapsedTime);

	const auto& state = m_commonResources->GetInputManager()->GetMouseState();

	const auto& tracker = m_commonResources->GetInputManager()->GetMouseTracker();

	//画面サイズの取得
	float widht = static_cast<float>( m_commonResources->GetDeviceResources()->GetOutputSize().right);
	float height = static_cast<float>(m_commonResources->GetDeviceResources()->GetOutputSize().bottom);



	Vector2 mousePosition = Vector2(state.x * Screen::WIDTH / widht, state.y * Screen::HEIGHT / height);


	//初期化
	m_selectButtomId = BUTTOM_INIAL_ID;

	for (auto& buttom : m_buttom)
	{
		buttom.second->SetScale(buttom.second->GetInialScale());
		if (WataLib::DetectionCollision::Circle_RectCheckHit(mousePosition, Params::MOUSE_RADIUS,
			buttom.second->GetPosition(), static_cast<float>(buttom.second->GetWidth()), static_cast<float>(buttom.second->GetHeight())))
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
			ShowCursor(FALSE);

			switch (m_selectButtomId)
			{
				case 0:
					m_sceneManager->SetStageID(SceneManager::STAGE1);
					break;
				case 1:
					m_sceneManager->SetStageID(SceneManager::STAGE2);
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
void StageSelectScene::SceneRender()
{

	for (auto& texture : m_textures)
	{
		texture->Render();
	}

	for (auto& buttom : m_buttom)
	{
		buttom.second->Render();
	}

	////// デバッグ情報を表示する
	//auto debugString = m_commonResources->GetDebugString();
	//////debugString->AddString("Pos %f" ,m_buttom[0]->GetPosition().x);
	//////debugString->AddString("Pos %f" ,m_buttom[0]->GetPosition().y);
	//debugString->AddString("X %d", m_commonResources->GetDeviceResources()->GetOutputSize().right);
	//debugString->AddString("Y %d", m_commonResources->GetDeviceResources()->GetOutputSize().bottom);



}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void StageSelectScene::Finalize()
{
	// do nothing.
}

