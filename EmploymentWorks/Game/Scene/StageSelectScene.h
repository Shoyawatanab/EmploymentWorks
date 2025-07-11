/*
    �N���X��     : StageSelectScene
    ����         : �Z���N�g�V�[��
    �⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "Game/Scene/SceneManager.h"



class StageSelectScene  :  public Scene
{
public:
    //�J�����̎擾
	Camera* GetCamera() const override { return m_camera; };


public:
    //�R���X�g���N�^
    StageSelectScene(SceneManager* sceneManager);
    //�f�X�g���N�^
    ~StageSelectScene() override;
    //������
    void Initialize() override;
    
private:
    Camera* m_camera;


};
