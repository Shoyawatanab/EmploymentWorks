/*
	@file	StageSelectScene.h
	@brief	�^�C�g���V�[���N���X
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "Game/Scene/SceneManager.h"
#include "Libraries/WataLib/UserInterface.h"



class StageSelectScene  :  public Scene
{
public:
    //�J�����̎擾
	Camera* GetCamera() const override { return m_camera; };


public:

    StageSelectScene(SceneManager* sceneManager);
    
    ~StageSelectScene() override;
    
    void Initialize() override;
    
    void SceneUpdate(const float& deltaTime)override;
    
    void SceneRender() override;
    
    void Finalize() override;


private:
    Camera* m_camera;


};
