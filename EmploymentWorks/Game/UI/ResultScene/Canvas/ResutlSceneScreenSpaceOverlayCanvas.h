/*
	クラス名     : ResutlSceneScreenSpaceOverlayCanvas
	説明         : リザルトシーンの常に移るUIキャンバス
	補足・注意点 :
*/
#pragma once
#include "GameBase/UI/Canvas/ScreenSpaceOverlayCanvas.h"


class ResutlSceneScreenSpaceOverlayCanvas : public ScreenSpaceOverlayCanvas
{
public:
	//コンストラクタ
	ResutlSceneScreenSpaceOverlayCanvas(Scene* scene);
	//デストラクタ
	~ResutlSceneScreenSpaceOverlayCanvas() override;

};
