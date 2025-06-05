/*
	@file	PlayScene.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "SceneManager.h"
#include "Game/Interface/IObserver.h"

// �O���錾
class StageObjectManager;
class Player;
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

class PlayScene  :  public Scene ,public IObserver<GamePlayMessageType>
{
public:

	Camera* GetCamera() const  override { return m_camera; };


public:
	//�R���X�g���N�^
	PlayScene(SceneManager::StageID stageID);
	//�f�X�g���N�^
	~PlayScene() override;




private:

	Camera* m_camera;
	


public:

	void Initialize() override;
	void SceneUpdate(float elapsedTime)override;
	void SceneRender() override;

	void Finalize() override;
	
	SceneID GetSceneID() const override { return SceneID::PLAY; }

	void SetNextSceneID(SceneID ID) { m_nextScene = ID; }

private:


	//�ʒm���ɌĂяo�����
	void Notify(const Telegram<GamePlayMessageType>& telegram) override;


private:


	// �V�[���`�F���W�t���O
	bool m_isChangeScene;
	//���̃V�[��
	SceneID m_nextScene;



};
