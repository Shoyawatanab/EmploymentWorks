/*
	@file	PlayScene.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "IScene.h"
#include <unordered_map>
#include "Game/Scene/SceneManager.h"
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
class BirdEnemy;
class HitEffects;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
	class GameCameraManager;
	class Texture;

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

	//スロー演出の進行割合を取得
	float GetSlowMotionProgressRate() { return m_progressRate; }

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
	std::unique_ptr<BirdEnemy> m_birdEnemy;

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


	//パーティクルクラス 爆発エフェクト
	std::vector<std::unique_ptr<Particle>> m_particle;

	// オーディオ関連
	std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
	std::unique_ptr<DirectX::SoundEffect> m_soundEffectBGM;
	std::unique_ptr<DirectX::SoundEffectInstance> m_soundEffectInstanceBGM;


	//初めのカウントダウン
	float m_startCountDown;


	//イベントの更新関数の格納変数
	std::unordered_map<std::string, std::function<void(float)>> m_eventUpdate;
	//削除したいイベント名の登録変数
	std::vector<std::string> m_deleteEventName;

	//スロー演出時の速度
	float m_slowMotionSpeed;
	//スロー演出の時間
	float m_slowMotionTime;
	//スロー演出の最大時間
	float m_slowMotionMaxTime;
	//スロー演出の表示画像
	std::unique_ptr<mylib::Texture> m_slowTexture;
	//スロー演出中かどうか
	bool m_isSlowMotion;
	//スロー演出の進行割合
	float m_progressRate;


	//ヒットエフェクト
	std::vector<std::unique_ptr<HitEffects>> m_hitEffects;
	
	SceneManager::StageID m_stageID;

public:
	PlayScene(SceneManager::StageID stageID);
	~PlayScene() override;

	void Initialize(CommonResources* resources) override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const override;


	void CreateStage();

	void CreateObject();

	//爆発エフェクトを生成
	void CreateParticle(DirectX::SimpleMath::Vector3 Pos);

	void CreateHitEffects(DirectX::SimpleMath::Vector3 Pos);


	//ブーメランを投げるときのスロー演出時に呼ばれる関数
	void BoomerangSlowMotion();
	//ブーメランの投げ終わり
	void BoomerangSlowMotionEnd();

	//スロー演出のUpdate
	void SlowMotion(float elapsdTime);

};
