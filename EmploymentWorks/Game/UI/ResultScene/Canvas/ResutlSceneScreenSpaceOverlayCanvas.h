/*
	�N���X��     : ResutlSceneScreenSpaceOverlayCanvas
	����         : ���U���g�V�[���̏�Ɉڂ�UI�L�����o�X
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/UI/Canvas/ScreenSpaceOverlayCanvas.h"


class ResutlSceneScreenSpaceOverlayCanvas : public ScreenSpaceOverlayCanvas
{
public:
	//�R���X�g���N�^
	ResutlSceneScreenSpaceOverlayCanvas(Scene* scene);
	//�f�X�g���N�^
	~ResutlSceneScreenSpaceOverlayCanvas() override;

};
