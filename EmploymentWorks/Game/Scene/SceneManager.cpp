/*
	@file	SceneManager.cpp
	@brief	�V�[���}�l�[�W���N���X
*/
#include "pch.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "StageSelectScene.h"
#include "Game/Screen.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>

#include "Libraries/MyLib/Fade.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
SceneManager::SceneManager()
	:
	m_currentScene{},
	m_commonResources{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
SceneManager::~SceneManager()
{
	Finalize();
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void SceneManager::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;


	m_stageID = StageID::Stage1;

	ChangeScene(IScene::SceneID::STAGESELECT);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void SceneManager::Update(float elapsedTime)
{
	//���݂̃V�[���̍X�V
	m_currentScene->Update(elapsedTime);

	// �����p�ϐ��F���̃V�[��
	const IScene::SceneID nextSceneID = m_currentScene->GetNextSceneID();

	// �V�[����ύX���Ȃ��Ƃ�
	if (nextSceneID == IScene::SceneID::NONE) return;

	if (m_commonResources->GetFade()->GetIsSceneChange())
	{
		// �V�[����ύX����
		ChangeScene(nextSceneID);
	}

	





}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void SceneManager::Render()
{
	//���݂̃V�[���̕`��
	m_currentScene->Render();

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void SceneManager::Finalize()
{
	DeleteScene();
}

//---------------------------------------------------------
// �V�[����ύX����
//---------------------------------------------------------
void SceneManager::ChangeScene(IScene::SceneID sceneID)
{
	DeleteScene();
	CreateScene(sceneID);
}

//---------------------------------------------------------
// �V�[�����쐬����
//---------------------------------------------------------
void SceneManager::CreateScene(IScene::SceneID sceneID)
{
	assert(m_currentScene == nullptr);



	switch (sceneID)
	{
		case IScene::SceneID::TITLE:
			m_currentScene = std::make_unique<TitleScene>();
			break;
		case IScene::SceneID::PLAY:


			m_currentScene = std::make_unique<PlayScene>(m_stageID);
			break;
		case IScene::SceneID::STAGESELECT:
			m_currentScene = std::make_unique<StageSelectScene>(this);
			break;
		case IScene::SceneID::RESULT:
			m_currentScene = std::make_unique<ResultScene>();
			break;
		default:
			assert(!"SceneManager::CreateScene::�V�[���������݂��܂���I");
			// no break
	}

	assert(m_currentScene && "SceneManager::CreateScene::���̃V�[������������܂���ł����I");
	m_currentScene->Initialize(m_commonResources);
}

//---------------------------------------------------------
// �V�[�����폜����
//---------------------------------------------------------
void SceneManager::DeleteScene()
{
	if (m_currentScene)
	{
		m_currentScene.reset();
	}
}
