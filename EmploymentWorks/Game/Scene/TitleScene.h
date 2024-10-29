/*
	@file	TitleScene.h
	@brief	タイトルシーンクラス
*/
#pragma once
#include "IScene.h"

// 前方宣言
class CommonResources;
class Player;
class Enemy;
class Floor;
class Wall;
class Ceiling;
class Pillar;
class Artillery;



namespace mylib
{
	class TitleCamera;
	class GridFloor;
	class Texture;
	class Model3D;
	class LoadJson;

}


class TitleScene final :
    public IScene
{
public:
	enum class NextState
	{
		PLAY,
		EXIT

	};
private:
	// 共通リソース
	CommonResources* m_commonResources;
	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;


	std::unique_ptr<mylib::TitleCamera> m_camera;

	// シーンチェンジフラグ
	bool m_isChangeScene;
	//ロゴ
	std::unique_ptr<mylib::Texture> m_logo;
	//PLAY画像
	std::unique_ptr<mylib::Texture> m_playTexture;
	//EXIT画像
	std::unique_ptr<mylib::Texture> m_exitTexture;
	//Boomerang画像
	std::unique_ptr<mylib::Texture> m_boomerangTexture;

	//次の状態
	NextState m_state;


	std::vector<std::unique_ptr<mylib::Model3D>> m_models;

	std::unique_ptr<mylib::LoadJson> m_loadJson;
	std::unique_ptr<Player> m_player;
	std::unique_ptr<Enemy> m_enemy;
	//床
	std::unique_ptr<Floor> m_floor;

	//壁
	std::vector<std::unique_ptr<Wall>> m_wall;
	//天井
	std::unique_ptr<Ceiling> m_ceiling;
	//柱
	std::vector<std::unique_ptr<Pillar>> m_pillar;
	//砲台
	std::vector<std::unique_ptr<Artillery>> m_artillery;


public:
    TitleScene();
    ~TitleScene() override;

    void Initialize(CommonResources* resources) override;
    void Update(float elapsedTime)override;
    void Render() override;
    void Finalize() override;

    SceneID GetNextSceneID() const;


};
