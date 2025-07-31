/*
	�N���X��     : SceneManager
	����         : �V�[���}�l�[�W���[
	�⑫�E���ӓ_ :�@�V�[���̍쐬���̃N���X��SceneID�̓Q�[�����Ƃ̃N���X���g�p���邱��

*/
#pragma once
#include "GameBase/Messenger/IObserver.h"

// �O���錾
class Scene;
class FadeManager;

class SceneManager 
{
public:

	// �V�[��ID �Q�[�����ƂɃJ�X�^������
	enum class SceneID : unsigned int
	{
		NONE = 0,
		TITLE,
		PLAY,
		STAGESELECT,
		RESULT
	};

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
	//�t�F�[�h�}�l�[�W���[
	FadeManager* m_fadeManager;

};
