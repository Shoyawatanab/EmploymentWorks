/*
	@file	PlayScene.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "SceneManager.h"

// �O���錾

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

namespace WataLib
{
	class CameraManager;
}

class PlayScene  :  public Scene// ,public IObserver<GamePlayMessageType>
{
public:

	Camera* GetCamera() const  override { return m_camera; };


public:
	//�R���X�g���N�^
	PlayScene();
	//�f�X�g���N�^
	~PlayScene() override;

	void Initialize() override;

	void SceneUpdate(const float& deltaTime)override;

	void SceneRender() override;

	void Finalize() override;
	

private:


	// �V�[���`�F���W�t���O
	bool m_isChangeScene;
	//�J����
	Camera* m_camera;



};
