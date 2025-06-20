/*
	@file	TitleScene.cpp
	@brief	タイトルシーンクラス
*/
#include "pch.h"
#include "TitleScene.h"
#include "GameBase/Screen.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/WataLib/Fade.h"
#include <cassert>
#include "Libraries/WataLib/Json.h"
#include "Game/Stage/StageObjects.h"
#include "Game/Params.h"


#include "Libraries/MyLib/DebugString.h"



#include "Game/Camera/TitleScene/TitleSceneCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TitleScene::TitleScene()
	:
	m_projection{}

{

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TitleScene::~TitleScene()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TitleScene::Initialize()
{


	//カメラの作成
	m_camera = AddActor<TitleSceneCamera>(this);



	//WataLib::Json::StageData stageParameters;

	//std::unique_ptr<WataLib::Json> json = std::make_unique<WataLib::Json>();


	//stageParameters = json->LoadStageDatas(L"Stage");



	////auto model = std::make_unique<WataLib::Model3D>();
	////model->Initialize(m_commonResources, L"Resources/Models/Player.cmo",
	////	PLAYERPOSITION, PLAYERSCALE);

	////m_objects.push_back(std::move(model));

	//m_player = std::make_unique<Player>(m_commonResources);
	////m_player->Initialize();

	//m_player->SetPosition(PLAYERPOSITION);
	//m_player->SetScale(PLAYERSCALE);
	//m_player->SetRotation(DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
	//	DirectX::XMConvertToRadians(PLAYERROTATION.y),
	//	DirectX::XMConvertToRadians(PLAYERROTATION.x),
	//	DirectX::XMConvertToRadians(PLAYERROTATION.z)));

	//CreateTextures();

	// シーン変更フラグを初期化する
	m_isChangeScene = false;

	//フェードアウトの開始
	CommonResources::GetInstance()->GetFade()->StartNormalFadeOut();

	ShowCursor(true);



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
	if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		ChangeScene(SceneID::PLAY);

		//if (m_selectButtomId != BUTTOM_INIAL_ID)
		//{

		//	switch (m_selectButtomId)
		//	{
		//		case 0:
		//			m_isChangeScene = true;
		//			ChangeScene(SceneID::PLAY);
		//			break;
		//		case 1:
		//			PostQuitMessage(0);
		//			break;
		//		default:
		//			break;
		//	}
		//}
	}



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
