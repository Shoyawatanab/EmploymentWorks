/*
	�N���X��     : SelectSceneScreenSpaceOverlayCanvas
	����         : �Z���N�g�V�[���̏�ɉf�葱����UI�L�����o�XI
	�⑫�E���ӓ_ :
*/
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
