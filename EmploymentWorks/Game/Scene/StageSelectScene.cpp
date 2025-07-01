/*
	@file	StageSelectScene.cpp
	@brief	�^�C�g���V�[���N���X
*/
#include "pch.h"
#include "StageSelectScene.h"
#include "GameBase/Common/Commons.h"

#include "Game/Camera/SelectScene/SelectSceneCamera.h"
#include "Game/Camera/Normal/NormalCamera.h"

#include "Game/UI/SelectScene/Canvas/SelectSceneScreenSpaceOverlayCanvas.h"
#include "Game/Fade/FadeManager.h"


//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
StageSelectScene::StageSelectScene(SceneManager* sceneManager)
	:
	m_camera{}
{
	FadeManager::GetInstance()->StartFadeOut();

}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
StageSelectScene::~StageSelectScene()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void StageSelectScene::Initialize()
{

	//�J�����̍쐬
	m_camera =AddActor<SelectSceneCamera>(this);

	auto ui = AddActor<SelectSceneScreenSpaceOverlayCanvas>(this);


}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void StageSelectScene::SceneUpdate(const float& deltaTime)
{

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void StageSelectScene::SceneRender()
{

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void StageSelectScene::Finalize()
{
	// do nothing.
}

