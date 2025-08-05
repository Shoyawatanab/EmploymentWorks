/*
	�N���X��     : SceneManager
	����         : �V�[���}�l�[�W���[
	�⑫�E���ӓ_ :�@�V�[���̍쐬���̃N���X��SceneID�̓Q�[�����Ƃ̃N���X���g�p���邱��
*/
#include "pch.h"
#include "SceneManager.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Screen.h"
#include "GameBase/Common/Commons.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Fade/FadeManager.h"


//�Q�[�����Ƃ̃V�[��
#include "Game/Scene/TitleScene.h"
#include "Game/Scene/PlayScene.h"
#include "Game/Scene/ResultScene.h"
#include "Game/Scene/StageSelectScene.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager()
	:
	m_currentScene{}
	,m_fadeManager{}
{

	m_fadeManager = FadeManager::GetInstance();


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneManager::~SceneManager()
{
	Finalize();
}

/// <summary>
/// ������
/// </summary>
void SceneManager::Initialize()
{

	//�����V�[��
	ChangeScene(SceneID::TITLE);

}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void SceneManager::Update(float elapsedTime)
{
	//�V�[���̍X�V
	m_currentScene->Update(elapsedTime);

	//�V�[��ID�̎擾
	auto nextSceneID = m_currentScene->GetNextSceneID();

	// �V�[����ύX���Ȃ��Ƃ�
	if (nextSceneID == SceneID::NONE) return;

	//�t�F�[�h
	if (m_fadeManager->GetFadeState() != FadeManager::FadeState::NONE)
	{
		return;
	}

	//�V�[���؂�ւ�
	ChangeScene(nextSceneID);
	
}

/// <summary>
/// �`��
/// </summary>
void SceneManager::Render()
{
	//�V�[���̕`��
	m_currentScene->Render();
}


/// <summary>
/// ��n��
/// </summary>
void SceneManager::Finalize()
{
	//�V�[���̍폜
	DeleteScene();
}


/// <summary>
/// �V�[���ύX
/// </summary>
/// <param name="sceneID"></param>
void SceneManager::ChangeScene(SceneID sceneID)
{
	//�V�[���̍폜
	DeleteScene();
	//�V�[���̍쐬
	CreateScene(sceneID);
}

/// <summary>
/// �V�[���̍쐬
/// </summary>
/// <param name="sceneID"></param>
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
			m_currentScene = std::make_unique<StageSelectScene>();
			break;
		case SceneID::RESULT:
			m_currentScene = std::make_unique<ResultScene>();
			break;
		default:
			assert(!"SceneManager::CreateScene::�V�[���������݂��܂���I");
	}

	assert(m_currentScene && "SceneManager::CreateScene::���̃V�[������������܂���ł����I");
	m_currentScene->Initialize();

}


/// <summary>
/// �V�[���̍폜
/// </summary>
void SceneManager::DeleteScene()
{
	if (m_currentScene)
	{
		m_currentScene.reset();
	}
}






