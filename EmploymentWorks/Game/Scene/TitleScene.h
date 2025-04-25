/*
	@file	TitleScene.h
	@brief	タイトルシーンクラス
*/
#pragma once
#include "IScene.h"
#include "Game/Entities/BaseEntity.h"
#include <unordered_map>
#include "Libraries/WataLib/UserInterface.h"
#include "Game/Player/Player.h"

// 前方宣言
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

    //拡大率
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
    // 共通リソース
    CommonResources* m_commonResources;
    // 射影行列
    DirectX::SimpleMath::Matrix m_projection;

    State m_state;

    // シーンチェンジフラグ
    bool m_isChangeScene;

    std::vector<std::unique_ptr< BaseEntity>> m_object;
    //モデル
    std::vector<  std::unique_ptr<WataLib::Model3D>> m_objects;
    //カメラ
    std::unique_ptr<WataLib::TitleCamera> m_camera;
    //
    std::vector<std::unique_ptr<UserInterface>> m_textures;

    std::unordered_map<int,std::unique_ptr<UserInterface>> m_buttom;

    int m_selectButtomId;

    std::unique_ptr<Player> m_player;

};
