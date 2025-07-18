/*
	クラス名     : SelectSceneScreenSpaceOverlayCanvas
	説明         : セレクトシーンの常に映り続けるUIキャンバスI
	補足・注意点 :
*/
#include "pch.h"
#include "SelectSceneScreenSpaceOverlayCanvas.h"
#include "Game/UI/SelectScene/SelectSceneUIs.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
SelectSceneScreenSpaceOverlayCanvas::SelectSceneScreenSpaceOverlayCanvas(Scene* scene)
	:
	ScreenSpaceOverlayCanvas(scene)
{
	using namespace DirectX::SimpleMath;

	//背景の作成
	GetScene()->AddActor<SelectSceneBackGraund>(this);

	//各ボタン
	GetScene()->AddActor<StageOneButton>(this);
	GetScene()->AddActor<StageTwoButton>(this);

}

/// <summary>
/// デストラクタ
/// </summary>
SelectSceneScreenSpaceOverlayCanvas::~SelectSceneScreenSpaceOverlayCanvas()
{
}
