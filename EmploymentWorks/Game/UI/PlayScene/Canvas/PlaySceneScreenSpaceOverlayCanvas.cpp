#include "pch.h"
#include "PlaySceneScreenSpaceOverlayCanvas.h"
#include "GameBase/Scene/Scene.h"
#include "Game/UI/PlayScene/PlayerHp/PlayerHp.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
PlaySceneScreenSpaceOverlayCanvas::PlaySceneScreenSpaceOverlayCanvas(Scene* scene)
	:
	ScreenSpaceOverlayCanvas(scene)
{

	//PlyerHp�̍쐬
	//auto playerHp = GetScene()->AddActor<PlayerHp>(this);



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlaySceneScreenSpaceOverlayCanvas::~PlaySceneScreenSpaceOverlayCanvas()
{
}

