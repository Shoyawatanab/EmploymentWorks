#pragma once
#include "GameBase/UI/Canvas/ScreenSpaceOverlayCanvas.h"


class SelectSceneScreenSpaceOverlayCanvas : public ScreenSpaceOverlayCanvas
{
public:
	//�R���X�g���N�^
	SelectSceneScreenSpaceOverlayCanvas(Scene* scene);
	//�f�X�g���N�^
	~SelectSceneScreenSpaceOverlayCanvas() override;

};
