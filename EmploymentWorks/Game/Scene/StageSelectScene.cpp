/*
	�N���X��     : StageSelectScene
	����         : �Z���N�g�V�[��
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "StageSelectScene.h"
#include "GameBase/Common/Commons.h"

#include "Game/Camera/SelectScene/SelectSceneCamera.h"
#include "Game/Camera/Normal/NormalCamera.h"

#include "Game/UI/SelectScene/Canvas/SelectSceneScreenSpaceOverlayCanvas.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Sound/SelectScene/SelectSceneSound.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
StageSelectScene::StageSelectScene()
	:
	m_camera{}
{
	//FadeManager::GetInstance()->StartFadeOut();
	FadeManager::GetInstance()->StartFadeOut(FadeManager::FadeOutKinds::BOMERANG_FADE_OUT);



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageSelectScene::~StageSelectScene()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
void StageSelectScene::SceneInitialize()
{

	//�J�����̍쐬
	m_camera =AddActor<SelectSceneCamera>(this);

	AddActor<SelectSceneScreenSpaceOverlayCanvas>(this);

	AddActor<SelectSceneSound>(this);

}



