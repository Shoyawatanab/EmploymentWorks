/*
	@file	SceneManager.h
	@brief	�V�[���}�l�[�W���N���X
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Global/GlobalMeesageType.h"

// �O���錾
class FadeManager;

class SceneManager : public IObserver<GlobalMessageType>
{
public:

	// �V�[��ID
	enum class SceneID : unsigned int
	{
		NONE,
		TITLE,
		PLAY,
		STAGESELECT,
		RESULT
	};

	enum StageID
	{
		STAGE1 = 0,
		STAGE2

	};
public:

	//���̃V�[����ID�̃Z�b�g
	void SetNextSceneID(SceneID sceneID) { m_nextSceneID =  sceneID; }

public:
	//�R���X�g���N
	SceneManager();
	//�f�X�g���N�^
	~SceneManager();
	//������
	void Initialize();
	//�X�V����
	void Update(float elapsedTime);
	//�`��
	void Render();
	//
	void Finalize();

	//�ʒm���ɌĂяo�����
	void Notify(GlobalMessageType type, void* datas) override;



private:
	//�V�[���؂�ւ�
	void ChangeScene(SceneID sceneID);
	//�V�[���̍쐬
	void CreateScene(SceneID sceneID);
	//�V�[���̍폜
	void DeleteScene();

private:
	//���s�V�[��
	std::unique_ptr<Scene> m_currentScene;
	//���̃V�[��
	SceneID m_nextSceneID;

	//�t�F�[�h�}�l�[�W���[
	FadeManager* m_fadeManager;

};
