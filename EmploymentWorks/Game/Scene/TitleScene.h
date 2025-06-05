/*
	@file	TitleScene.h
	@brief	�^�C�g���V�[���N���X
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "Game/Entities/BaseEntity.h"
#include <unordered_map>
#include "Libraries/WataLib/UserInterface.h"
#include "Game/Player/Player.h"

// �O���錾
class CommonResources;

namespace WataLib
{
    class Model3D;
}


class TitleScene :  public Scene
{

private:


    static constexpr DirectX::SimpleMath::Vector3 PLAYERPOSITION {0.0f,0.8f,0.0f};
    static constexpr DirectX::SimpleMath::Vector3 PLAYERSCALE {0.3f,0.3f,0.3f};
    static constexpr DirectX::SimpleMath::Vector3 PLAYERROTATION {0.0f,180.0f,0.0f};

    //�g�嗦
    static constexpr float EXPANSION{ 1.2f };

    static constexpr int BUTTOM_INIAL_ID{ -1000 };

public:

    enum class State
    {
        PLAY,
        EXIT

    };

public:
    Camera* GetCamera() const  override { return m_camera; };


public:
    TitleScene();
    ~TitleScene() override;


private:
    Camera* m_camera;



public:
    void Initialize() override;
    void SceneUpdate(float elapsedTime)override;
    void SceneRender() override;
    void Finalize() override;

    SceneID GetSceneID() const override { return SceneID::TITLE; }

    void CreateTextures();

private:
    // �ˉe�s��
    DirectX::SimpleMath::Matrix m_projection;

    State m_state;

    // �V�[���`�F���W�t���O
    bool m_isChangeScene;

    std::vector<std::unique_ptr< BaseEntity>> m_object;
    //���f��
    std::vector<  std::unique_ptr<WataLib::Model3D>> m_objects;
    //
    std::vector<std::unique_ptr<UserInterface>> m_textures;

    std::unordered_map<int,std::unique_ptr<UserInterface>> m_buttom;

    int m_selectButtomId;

    std::unique_ptr<Player> m_player;

};
