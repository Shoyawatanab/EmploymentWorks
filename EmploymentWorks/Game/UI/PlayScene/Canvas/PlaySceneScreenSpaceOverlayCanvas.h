/*
プレイシーンのカメラの常に移るUiキャンバスクラス
*/
#pragma once
#include "GameBase/UI/Canvas/ScreenSpaceOverlayCanvas.h"


class PlaySceneScreenSpaceOverlayCanvas : public ScreenSpaceOverlayCanvas
{
public:
	//コンストラクタ
	PlaySceneScreenSpaceOverlayCanvas(Scene* scene);
	//デストラクタ
	~PlaySceneScreenSpaceOverlayCanvas();

};
