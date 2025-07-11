/*
	�N���X��     : SelectSceneScreenSpaceOverlayCanvas
	����         : �Z���N�g�V�[���̏�ɉf�葱����UI�L�����o�XI
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "SelectSceneScreenSpaceOverlayCanvas.h"
#include "Game/UI/SelectScene/SelectSceneUIs.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
SelectSceneScreenSpaceOverlayCanvas::SelectSceneScreenSpaceOverlayCanvas(Scene* scene)
	:
	ScreenSpaceOverlayCanvas(scene)
{
	using namespace DirectX::SimpleMath;

	//�w�i�̍쐬
	GetScene()->AddActor<SelectSceneBackGraund>(this);

	//�e�{�^��
	GetScene()->AddActor<StageOneButton>(this);
	GetScene()->AddActor<StageTwoButton>(this);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SelectSceneScreenSpaceOverlayCanvas::~SelectSceneScreenSpaceOverlayCanvas()
{
}
