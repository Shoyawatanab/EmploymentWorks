/*
	@file	ResultScene.cpp
	@brief	タイトルシーンクラス
*/
#include "pch.h"
#include "ResultScene.h"
#include "GameBase/Screen.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>

#include "Libraries/WataLib/Fade.h"
#include "Game/Score.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
ResultScene::ResultScene()
	:
	m_isChangeScene{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
ResultScene::~ResultScene()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void ResultScene::Initialize()
{





	// シーン変更フラグを初期化する
	m_isChangeScene = false;


	//フェードアウトの開始
	CommonResources::GetInstance()->GetFade()->StartNormalFadeOut();

	CommonResources::GetInstance()->GetScore()->Reset();

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void ResultScene::SceneUpdate(float elapsedTime)
{
	// 宣言をしたが、実際は使用していない変数
	UNREFERENCED_PARAMETER(elapsedTime);

	//フェードが終わるまで
	if (CommonResources::GetInstance()->GetFade()->GetFadeState() != Fade::FadeState::NONE)
	{
		return;
	}


	CommonResources::GetInstance()->GetScore()->Update(elapsedTime);

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void ResultScene::SceneRender()
{

	CommonResources::GetInstance()->GetScore()->Render();

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void ResultScene::Finalize()
{
	// do nothing.
}


