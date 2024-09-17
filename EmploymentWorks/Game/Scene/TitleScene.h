/*
	@file	TitleScene.h
	@brief	タイトルシーンクラス
*/
#pragma once
#include "IScene.h"

// 前方宣言
class CommonResources;



namespace mylib
{
	class TitleCamera;
	class GridFloor;
	class Texture;
	class Model3D;
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


public:
    TitleScene();
    ~TitleScene() override;

    void Initialize(CommonResources* resources) override;
    void Update(float elapsedTime)override;
    void Render() override;
    void Finalize() override;

    SceneID GetNextSceneID() const;



};
