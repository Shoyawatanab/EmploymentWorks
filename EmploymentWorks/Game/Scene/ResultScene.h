/*
	@file	ResultScene.h
	@brief	�^�C�g���V�[���N���X
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "Game/Scene/SceneManager.h"

// �O���錾
class CommonResources;





class ResultScene  :  public Scene
{

public:
    Camera* GetCamera() const  override { return m_camera; };


public:
    ResultScene();
    ~ResultScene() override;

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
