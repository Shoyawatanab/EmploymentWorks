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
class CollisionManager;
class Wall;
class Rock;
class Sky;
class UI;
class Ceiling;
class Pillar;
class Artillery;
class Particle;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
	class GameCameraManager;
	class LoadJson;

}


class PlayScene final :
	public IScene
{
public:

	enum class GameState
	{
		None,    //通常
		Clear,
		GameOver

	};

public:

	void SetNextSceneID(SceneID ID) { m_nextScene = ID; }

private:

	SceneID m_nextScene;

	// 共通リソース
	CommonResources* m_commonResources;

	// デバッグカメラ
	//std::unique_ptr<mylib::DebugCamera> m_debugCamera;

	std::unique_ptr<mylib::GameCameraManager> m_cameraManager;

	// 格子床
	std::unique_ptr<mylib::GridFloor> m_gridFloor;

	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;

	std::unique_ptr<Player> m_player;
	std::unique_ptr<Enemy> m_enemy;
	//床
	std::unique_ptr<Floor> m_floor;
	std::unique_ptr<LockOn> m_lockOn;

	//壁
	std::vector<std::unique_ptr<Wall>> m_wall;
	//天井
	std::unique_ptr<Ceiling> m_ceiling;
	//柱
	std::vector<std::unique_ptr<Pillar>> m_pillar;
	//砲台
	std::vector<std::unique_ptr<Artillery>> m_artillery;

	std::unique_ptr<CollisionManager> m_collisionManager;

	std::unique_ptr<UI> m_ui;


	std::vector< std::unique_ptr<Rock>> m_rock;


	std::unique_ptr<Sky> m_sky;

	GameState m_state;

	//Jsonファイルの読み込みクラス
	std::unique_ptr<mylib::LoadJson> m_loadJson;

	//パーティクルクラス 爆発エフェクト
	std::vector<std::unique_ptr<Particle>> m_particle;

	// オーディオ関連
	std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
	std::unique_ptr<DirectX::SoundEffect> m_soundEffectBGM;
	std::unique_ptr<DirectX::SoundEffectInstance> m_soundEffectInstanceBGM;


	//初めのカウントダウン
	float m_startCountDown;
public:
	PlayScene();
	~PlayScene() override;

	void Initialize(CommonResources* resources) override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const override;



	void CreateParticle(DirectX::SimpleMath::Vector3 Pos);

};
