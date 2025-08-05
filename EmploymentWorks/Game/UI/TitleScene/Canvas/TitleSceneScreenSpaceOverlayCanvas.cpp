/*
	�N���X��     : TitleSceneScreenSpaceOverlayCanvas
	����         : �^�C�g���V�[���̏�ɉf�葱����UI�L�����o�X
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "TitleSceneScreenSpaceOverlayCanvas.h"
#include "Game/UI/TitleScene/TitleSceneUIs.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
TitleSceneScreenSpaceOverlayCanvas::TitleSceneScreenSpaceOverlayCanvas(Scene* scene)
	:
	ScreenSpaceOverlayCanvas(scene)
{
	using namespace DirectX::SimpleMath;

	auto logo =GetScene()->AddActor<Image>(this,"Logo");
	logo->GetTransform()->SetPosition(LOGO_POSITION);
	logo->GetTransform()->SetScale(LOGO_SCALE);

	//
	GetScene()->AddActor<ExitButton>(this);
	GetScene()->AddActor<PlayButton>(this);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleSceneScreenSpaceOverlayCanvas::~TitleSceneScreenSpaceOverlayCanvas()
{
}
