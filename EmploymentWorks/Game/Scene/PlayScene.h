/*
	@file	PlayScene.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "IScene.h"
#include "SceneManager.h"

// �O���錾
class CommonResources;
class StageObjectManager;
class Player;
class EnemyManager;
class CollisionManager;
class UIManager;
class TargetMarker;
class EffectsManager;
class Sky;
class UserInterface;
class SoundManager;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

namespace WataLib
{
	class CameraManager;
}

class PlayScene final :
    public IScene
{
public:
	//�R���X�g���N�^
	PlayScene(SceneManager::StageID stageID);
	//�f�X�g���N�^
	~PlayScene() override;

	//������
	void Initialize(CommonResources* resources) override;
	//�X�V
	void Update(float elapsedTime)override;
	//�`��
	void Render() override;

	void Finalize() override;
	
	//�V�[���؂�ւ�
	SceneID GetNextSceneID() const;

	void SetNextSceneID(SceneID ID) { m_nextScene = ID; }

private:
	//�X�e�[�W���쐬
	void CreateStageObject();
	//�}�E�X�z�C�[���̃`�F�b�N
	void CheckMouseWheel();


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	//�v���C��
	std::unique_ptr<Player> m_player;
	//�X�e�[�W�I�u�W�F�N�g�}�l�[�W���[
	std::unique_ptr<StageObjectManager> m_stageObjectManager;
	//
	std::unique_ptr<EnemyManager> m_enemyManager;
	//�J�����}�l�[�W���[
	std::unique_ptr<WataLib::CameraManager> m_cameraManager;
	//�����蔻��}�l�[�W���[
	std::unique_ptr<CollisionManager> m_collisionManager;
	//UI�}�l�[�W���[
	std::unique_ptr<UIManager> m_uiManager;
	//�^�[�Q�b�g�}�[�J�[
	std::unique_ptr<TargetMarker> m_targetMarker;
	//�G�t�F�N�g�}�C�N���\�t�g
	std::unique_ptr<EffectsManager> m_effectsManager;
	SceneManager::StageID m_stageID;

	//�`���[�g���A���摜
	std::unique_ptr<UserInterface> m_tutorialTex;

	std::unique_ptr<Sky> m_sky;

	
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;

	// �V�[���`�F���W�t���O
	bool m_isChangeScene;
	//���̃V�[��
	SceneID m_nextScene;

	bool m_isTutolialTex;

	SoundManager* m_soundManager;

};
