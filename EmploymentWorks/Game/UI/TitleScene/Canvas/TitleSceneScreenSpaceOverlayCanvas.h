/*
	クラス名     : TitleSceneScreenSpaceOverlayCanvas
	説明         : タイトルシーンの常に映り続けるUIキャンバス
	補足・注意点 :
*/
#pragma once
#include "GameBase/UI/Canvas/ScreenSpaceOverlayCanvas.h"


class TitleSceneScreenSpaceOverlayCanvas : public ScreenSpaceOverlayCanvas
{
public:
	//コンストラクタ
	TitleSceneScreenSpaceOverlayCanvas(Scene* scene);
	//デストラクタ
	~TitleSceneScreenSpaceOverlayCanvas() override;

};
