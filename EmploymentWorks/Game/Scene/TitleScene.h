/*
    �N���X��     : TitleScene
    ����         : �^�C�g���V�[��
    �⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include <unordered_map>




class TitleScene :  public Scene
{

private:


    static constexpr DirectX::SimpleMath::Vector3 PLAYER_POSITION {0.0f,0.8f,0.0f};



public:
    //�J�����̎擾
    Camera* GetCamera() const  override { return m_camera; };


public:
    //�R���X�g���N 
    TitleScene();
    //�f�X�g���N�^
    ~TitleScene() override;
    //������
    void Initialize() override;    
private:
    //�J����
    Camera* m_camera;


};
