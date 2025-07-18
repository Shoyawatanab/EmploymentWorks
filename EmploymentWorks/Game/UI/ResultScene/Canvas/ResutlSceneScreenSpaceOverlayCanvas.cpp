/*
	クラス名     : ResutlSceneScreenSpaceOverlayCanvas
	説明         : リザルトシーンの常に移るUIキャンバス
	補足・注意点 :
*/
#include "pch.h"
#include "ResutlSceneScreenSpaceOverlayCanvas.h"
#include "Game/UI/TitleScene/TitleSceneUIs.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/UI/ResultScene/ResultSceneUIs.h"
#include "Game/UI/PlayScene/GameOver/TitleButton/TitleButton.h"
#include "Game/UI/PlayScene/GameOver/RetryButton/RetryButton.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
ResutlSceneScreenSpaceOverlayCanvas::ResutlSceneScreenSpaceOverlayCanvas(Scene* scene)
	:
	ScreenSpaceOverlayCanvas(scene)
{
	using namespace DirectX::SimpleMath;

	//背景
	GetScene()->AddActor<ResultSceneBackGraund>(this);

	//ボタン
	GetScene()->AddActor<ResultRetryButton>(this);
	GetScene()->AddActor<ResultTitleButton>(this);

	//タイム
	GetScene()->AddActor<ResultTime>(this);

}

/// <summary>
/// デストラクタ
/// </summary>
ResutlSceneScreenSpaceOverlayCanvas::~ResutlSceneScreenSpaceOverlayCanvas()
{
}
