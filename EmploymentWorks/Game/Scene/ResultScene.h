/*
    �N���X��     : ResultScene
    ����         : ���U���g�V�[��
    �⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "Game/Scene/SceneManager.h"

// �O���錾
class CommonResources;

class ResultScene  :  public Scene
{

public:
    //�J�����̎擾
    Camera* GetCamera() const  override { return m_camera; };


public:
    //�R���X�g���N�^
    ResultScene();
    //�f�X�g���N�^
    ~ResultScene() override;
    //������
    void SceneInitialize() override;

private:

	// �V�[���`�F���W�t���O
	bool m_isChangeScene;
    //�J����
    Camera* m_camera;

};
