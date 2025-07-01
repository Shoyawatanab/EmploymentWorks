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
#include "GameBase/Screen.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Fade/FadeManager.h"


//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
SceneManager::SceneManager()
	:
	m_currentScene{}
	,m_nextSceneID{}
	,m_fadeManager{}
{

	m_fadeManager = FadeManager::GetInstance();

	GlobalMessenger::GetInstance()->Rigister(
		{
			GlobalMessageType::CHANGE_TITLE_SCENE
			,GlobalMessageType::CHANGE_SELECT_SCENE
			,GlobalMessageType::CHANGE_PLAY_SCENE
			,GlobalMessageType::CHANGE_RESULT_SCENE
		}, this
	);

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
void SceneManager::Initialize()
{

	//�����V�[��
	ChangeScene(SceneID::PLAY);



}


//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void SceneManager::Update(float elapsedTime)
{
	m_currentScene->Update(elapsedTime);

	// �V�[����ύX���Ȃ��Ƃ�
	if (m_nextSceneID == SceneID::NONE) return;

	//�t�F�[�h
	if (m_fadeManager->GetFadeState() != FadeManager::FadeState::FADE_IN_END)
	{
		return;
	}

	//�V�[���؂�ւ�
	ChangeScene(m_nextSceneID);
	//������
	m_nextSceneID = SceneID::NONE;
	
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void SceneManager::Render()
{
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
void SceneManager::ChangeScene(SceneID sceneID)
{
	DeleteScene();
	CreateScene(sceneID);
}

//---------------------------------------------------------
// �V�[�����쐬����
//---------------------------------------------------------
void SceneManager::CreateScene(SceneID sceneID)
{
	assert(m_currentScene == nullptr);

	switch (sceneID)
	{
		case SceneID::TITLE:
			m_currentScene = std::make_unique<TitleScene>();
			break;
		case SceneID::PLAY:
			m_currentScene = std::make_unique<PlayScene>();
			break;
		case SceneID::STAGESELECT:
			m_currentScene = std::make_unique<StageSelectScene>(this);
			break;
		case SceneID::RESULT:
			m_currentScene = std::make_unique<ResultScene>();
			break;
		default:
			assert(!"SceneManager::CreateScene::�V�[���������݂��܂���I");
			// no break
	}

	assert(m_currentScene && "SceneManager::CreateScene::���̃V�[������������܂���ł����I");
	m_currentScene->Initialize();

}

//---------------------------------------------------------
// �V�[�����폜����
//---------------------------------------------------------
void SceneManager::DeleteScene()
{
	if (m_currentScene)
	{
		m_currentScene.reset();
		//���b�Z���W���[���N���A
		SceneMessenger::GetInstance()->Clear();

	}

}



/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void SceneManager::Notify(GlobalMessageType type, void* datas)
{
	switch (type)
	{
		case GlobalMessageType::CHANGE_TITLE_SCENE:
			SetNextSceneID(SceneID::TITLE);
			break;
		case GlobalMessageType::CHANGE_SELECT_SCENE:
			SetNextSceneID(SceneID::STAGESELECT);
			break;
		case GlobalMessageType::CHANGE_PLAY_SCENE:
			SetNextSceneID(SceneID::PLAY);
			break;
		case GlobalMessageType::CHANGE_RESULT_SCENE:
			SetNextSceneID(SceneID::RESULT);
			break;
		default:
			break;
	}
}



