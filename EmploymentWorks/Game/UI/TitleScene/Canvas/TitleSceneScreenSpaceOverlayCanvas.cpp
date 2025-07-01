#include "pch.h"
#include "TitleSceneScreenSpaceOverlayCanvas.h"
#include "Game/UI/TitleScene/TitleSceneUIs.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"

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
	logo->GetTransform()->SetPosition(Vector3(390,120,0));
	logo->GetTransform()->SetScale(Vector3(0.25,0.25,0));

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
