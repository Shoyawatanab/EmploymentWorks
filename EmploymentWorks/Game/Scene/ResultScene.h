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
    ResultScene();
    ~ResultScene() override;

    Camera* GetCamera() const { return nullptr; };




public:


    void Initialize() override;
    void SceneUpdate(float elapsedTime)override;
    void SceneRender() override;
    void Finalize() override;

	SceneID GetSceneID() const override { return SceneID::RESULT; }
private:


	// �V�[���`�F���W�t���O
	bool m_isChangeScene;

};
