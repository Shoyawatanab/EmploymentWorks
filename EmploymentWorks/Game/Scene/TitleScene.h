/*
	@file	TitleScene.h
	@brief	�^�C�g���V�[���N���X
*/
#pragma once
#include "IScene.h"
#include "Game/Entities/BaseEntity.h"
#include <unordered_map>
#include "Libraries/WataLib/UserInterface.h"
#include "Game/Player/Player.h"

// �O���錾
class CommonResources;

namespace WataLib
{
	class TitleCamera;
    class Model3D;
}


class TitleScene final :
    public IScene
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
    TitleScene();
    ~TitleScene() override;

    void Initialize(CommonResources* resources) override;
    void Update(float elapsedTime)override;
    void Render() override;
    void Finalize() override;

    SceneID GetNextSceneID() const;


    void CreateTextures();

private:
    // ���ʃ��\�[�X
    CommonResources* m_commonResources;
    // �ˉe�s��
    DirectX::SimpleMath::Matrix m_projection;

    State m_state;

    // �V�[���`�F���W�t���O
    bool m_isChangeScene;

    std::vector<std::unique_ptr< BaseEntity>> m_object;
    //���f��
    std::vector<  std::unique_ptr<WataLib::Model3D>> m_objects;
    //�J����
    std::unique_ptr<WataLib::TitleCamera> m_camera;
    //
    std::vector<std::unique_ptr<UserInterface>> m_textures;

    std::unordered_map<int,std::unique_ptr<UserInterface>> m_buttom;

    int m_selectButtomId;

    std::unique_ptr<Player> m_player;

};
