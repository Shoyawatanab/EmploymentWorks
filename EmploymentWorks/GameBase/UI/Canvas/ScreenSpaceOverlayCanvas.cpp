/*
	�N���X��     : ScreenSpaceOverlayCanvas
	����         : ��ɉ�ʂɉf���Ă���UI�pCanvas
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "ScreenSpaceOverlayCanvas.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
ScreenSpaceOverlayCanvas::ScreenSpaceOverlayCanvas(Scene* scene)
	:
	Canvas(scene,RenderType::SpaceOverlay)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ScreenSpaceOverlayCanvas::~ScreenSpaceOverlayCanvas()
{
}
