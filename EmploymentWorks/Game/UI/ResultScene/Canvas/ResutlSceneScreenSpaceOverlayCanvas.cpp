#include "pch.h"
#include "ResutlSceneScreenSpaceOverlayCanvas.h"
#include "Game/UI/TitleScene/TitleSceneUIs.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/UI/ResultScene/ResultSceneUIs.h"
#include "Game/UI/PlayScene/GameOver/TitleButton/TitleButton.h"
#include "Game/UI/PlayScene/GameOver/RetryButton/RetryButton.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
ResutlSceneScreenSpaceOverlayCanvas::ResutlSceneScreenSpaceOverlayCanvas(Scene* scene)
	:
	ScreenSpaceOverlayCanvas(scene)
{
	using namespace DirectX::SimpleMath;

	//�w�i
	GetScene()->AddActor<ResultSceneBackGraund>(this);

	//�{�^��
	GetScene()->AddActor<ResultRetryButton>(this);
	GetScene()->AddActor<ResultTitleButton>(this);

	//�^�C��
	GetScene()->AddActor<ResuktTime>(this);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResutlSceneScreenSpaceOverlayCanvas::~ResutlSceneScreenSpaceOverlayCanvas()
{
}
