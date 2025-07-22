/*
    �N���X��     : StageSelectScene
    ����         : �Z���N�g�V�[��
    �⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Scene/Scene.h"


class StageSelectScene  :  public Scene
{
public:
    //�J�����̎擾
	Camera* GetCamera() const override { return m_camera; };


public:
    //�R���X�g���N�^
    StageSelectScene();
    //�f�X�g���N�^
    ~StageSelectScene() override;
    //������
    void SceneInitialize() override;
    
private:
    Camera* m_camera;


};
