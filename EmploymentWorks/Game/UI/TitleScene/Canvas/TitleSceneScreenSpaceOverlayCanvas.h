/*
	�N���X��     : TitleSceneScreenSpaceOverlayCanvas
	����         : �^�C�g���V�[���̏�ɉf�葱����UI�L�����o�X
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/UI/Canvas/ScreenSpaceOverlayCanvas.h"


class TitleSceneScreenSpaceOverlayCanvas : public ScreenSpaceOverlayCanvas
{
public:
	//�R���X�g���N�^
	TitleSceneScreenSpaceOverlayCanvas(Scene* scene);
	//�f�X�g���N�^
	~TitleSceneScreenSpaceOverlayCanvas() override;

};
