/*
	@file	TitleScene.h
	@brief	�^�C�g���V�[���N���X
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include <unordered_map>
#include "Libraries/WataLib/UserInterface.h"




class TitleScene :  public Scene
{

private:


    static constexpr DirectX::SimpleMath::Vector3 PLAYER_POSITION {0.0f,0.8f,0.0f};



public:
    Camera* GetCamera() const  override { return m_camera; };


public:
    TitleScene();
    ~TitleScene() override;


private:



public:
    void Initialize() override;
    void SceneUpdate(const float& deltaTime)override;
    void SceneRender() override;
    void Finalize() override;

    void CreateTextures();

private:

    Camera* m_camera;


    // �ˉe�s��
    DirectX::SimpleMath::Matrix m_projection;


    // �V�[���`�F���W�t���O
    bool m_isChangeScene;


};
