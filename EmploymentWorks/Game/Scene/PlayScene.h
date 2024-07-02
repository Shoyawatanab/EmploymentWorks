/*
	@file	PlayScene.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "IScene.h"

// 前方宣言
class CommonResources;
class Player;
class Enemy;
class Floor;
class LockOn;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
	class TPS_Camera;
}


class PlayScene final :
    public IScene
{
private:
	// 共通リソース
	CommonResources* m_commonResources;

	// デバッグカメラ
	//std::unique_ptr<mylib::DebugCamera> m_debugCamera;

	std::unique_ptr<mylib::TPS_Camera> m_tpsCamera;

	// 格子床
	std::unique_ptr<mylib::GridFloor> m_gridFloor;

	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;

	// シーンチェンジフラグ
	bool m_isChangeScene;

	std::unique_ptr<Player> m_player;
	std::unique_ptr<Enemy> m_enemy ;

	std::unique_ptr<Floor> m_floor;
	std::unique_ptr<LockOn> m_lockOn;


public:
	PlayScene();
	~PlayScene() override;

	void Initialize(CommonResources* resources) override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;
};
