/*
	@file	TitleScene.cpp
	@brief	タイトルシーンクラス
*/
#include "pch.h"
#include "TitleScene.h"
#include "GameBase/Screen.h"
#include "GameBase/Common/Commons.h"
#include "Game/Camera/TitleScene/TitleSceneCamera.h"
#include "Game/UI/TitleScene/Canvas/TitleSceneScreenSpaceOverlayCanvas.h"
#include "Game/Stage/StageFactory.h"
#include "Game/Player/Model/PlayerModel.h"
#include "Game/Params.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
	:
	m_projection{}

{

}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize()
{


	//カメラの作成
	m_camera = AddActor<TitleSceneCamera>(this);

	//ステージファクトリー作成
	AddActor<StageFactory>(this);


	//モデルの作成
	auto model = AddActor<PlayerModel>(this);
	//モデルの大きさをプレイヤの設定に
	model->GetTransform()->SetScale(Params::PLAYER_SCALE);
	model->GetTransform()->Translate(PLAYER_POSITION);
	model->GetTransform()->SetRotate(Params::PLAYER_ROTATION);

	auto ui = AddActor<TitleSceneScreenSpaceOverlayCanvas>(this);

	//カメラのターゲットのセット
	m_camera->SetTargetPosition(model->GetTransform()->GetPosition() );




	//// シーン変更フラグを初期化する
	//m_isChangeScene = false;

	////フェードアウトの開始
	//CommonResources::GetInstance()->GetFade()->StartNormalFadeOut();

	//ShowCursor(true);



}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TitleScene::SceneUpdate(float elapsedTime)
{
	// 宣言をしたが、実際は使用していない変数
	UNREFERENCED_PARAMETER(elapsedTime);


	//const auto& state = m_commonResources->GetInputManager()->GetMouseState();

	const auto& tracker = CommonResources::GetInstance()->GetInputManager()->GetMouseTracker();

	//RECT rect{ m_commonResources->GetDeviceResources()->GetOutputSize() };

	////画面サイズの取得
	//float widht = static_cast<float>(m_commonResources->GetDeviceResources()->GetOutputSize().right);
	//float height = static_cast<float>(m_commonResources->GetDeviceResources()->GetOutputSize().bottom);

	//Vector2 mousePosition = Vector2(state.x * Screen::WIDTH / widht, state.y * Screen::HEIGHT / height) ;
	////Vector2 mousePosition = Vector2(state.x , state.y) ;
	//
	////初期化
	//m_selectButtomId = BUTTOM_INIAL_ID;
	//
	//for (auto& buttom : m_buttom)
	//{
	//	buttom.second->SetScale(buttom.second->GetInialScale());

	//	if (WataLib::DetectionCollision::Circle_RectCheckHit(Vector2(mousePosition.x,mousePosition.y), Params::MOUSE_RADIUS,
	//		buttom.second->GetPosition(), static_cast<float>(buttom.second->GetWidth()), static_cast<float>(buttom.second->GetHeight())))
	//	{
	//		buttom.second->SetScale(buttom.second->GetInialScale() * 1.4f);

	//		m_selectButtomId = buttom.first;
	//		break;

	//	}
	//}

	//
	//if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	//{
	//	ChangeScene(SceneID::PLAY);

	//	//if (m_selectButtomId != BUTTOM_INIAL_ID)
	//	//{

	//	//	switch (m_selectButtomId)
	//	//	{
	//	//		case 0:
	//	//			m_isChangeScene = true;
	//	//			ChangeScene(SceneID::PLAY);
	//	//			break;
	//	//		case 1:
	//	//			PostQuitMessage(0);
	//	//			break;
	//	//		default:
	//	//			break;
	//	//	}
	//	//}
	//}



}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TitleScene::SceneRender()
{




	////// デバッグ情報を表示する
	//auto debugString = m_commonResources->GetDebugString();
	//////debugString->AddString("Pos %f" ,m_buttom[0]->GetPosition().x);
	//////debugString->AddString("Pos %f" ,m_buttom[0]->GetPosition().y);
	//debugString->AddString("X %d" , m_commonResources->GetDeviceResources()->GetOutputSize().right);
	//debugString->AddString("Y %d" , m_commonResources->GetDeviceResources()->GetOutputSize().bottom);


}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TitleScene::Finalize()
{
	// do nothing.
}



void TitleScene::CreateTextures()
{


}
