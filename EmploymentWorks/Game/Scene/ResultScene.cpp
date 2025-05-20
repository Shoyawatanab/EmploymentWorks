/*
	@file	ResultScene.cpp
	@brief	タイトルシーンクラス
*/
#include "pch.h"
#include "ResultScene.h"
#include "Game/Screen.h"
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
	m_commonResources{},
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
void ResultScene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;





	// シーン変更フラグを初期化する
	m_isChangeScene = false;


	//フェードアウトの開始
	m_commonResources->GetFade()->StartNormalFadeOut();

	m_commonResources->GetScore()->Reset();

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void ResultScene::Update(float elapsedTime)
{
	// 宣言をしたが、実際は使用していない変数
	UNREFERENCED_PARAMETER(elapsedTime);

	//フェードが終わるまで
	if (m_commonResources->GetFade()->GetFadeState() != Fade::FadeState::NONE)
	{
		return;
	}


	m_commonResources->GetScore()->Update(elapsedTime);

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void ResultScene::Render()
{

	m_commonResources->GetScore()->Render();

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void ResultScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// 次のシーンIDを取得する
//---------------------------------------------------------
IScene::SceneID ResultScene::GetNextSceneID() const
{
	// シーン変更がある場合
	if (m_isChangeScene)
	{
		if (m_commonResources->GetFade()->GetFadeState() == Fade::FadeState::NONE)
		{
			m_commonResources->GetFade()->StartNormalFadeIn();
		}

		return IScene::SceneID::PLAY;
	}

	// シーン変更がない場合
	return IScene::SceneID::NONE;
}
