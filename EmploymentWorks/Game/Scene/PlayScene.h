/*
	@file	PlayScene.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "IScene.h"
#include "SceneManager.h"

// 前方宣言
class CommonResources;
class StageObjectManager;
class Player;
class EnemyManager;
class CollisionManager;
class UIManager;
class TargetMarker;
class EffectsManager;
class Sky;
class UserInterface;
class SoundManager;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

namespace WataLib
{
	class CameraManager;
}

class PlayScene final :
    public IScene
{
public:
	//コンストラクタ
	PlayScene(SceneManager::StageID stageID);
	//デストラクタ
	~PlayScene() override;

	//初期化
	void Initialize(CommonResources* resources) override;
	//更新
	void Update(float elapsedTime)override;
	//描画
	void Render() override;

	void Finalize() override;
	
	//シーン切り替え
	SceneID GetNextSceneID() const;

	void SetNextSceneID(SceneID ID) { m_nextScene = ID; }

private:
	//ステージを作成
	void CreateStageObject();
	//マウスホイールのチェック
	void CheckMouseWheel();


private:
	// 共通リソース
	CommonResources* m_commonResources;

	//プレイヤ
	std::unique_ptr<Player> m_player;
	//ステージオブジェクトマネージャー
	std::unique_ptr<StageObjectManager> m_stageObjectManager;
	//
	std::unique_ptr<EnemyManager> m_enemyManager;
	//カメラマネージャー
	std::unique_ptr<WataLib::CameraManager> m_cameraManager;
	//当たり判定マネージャー
	std::unique_ptr<CollisionManager> m_collisionManager;
	//UIマネージャー
	std::unique_ptr<UIManager> m_uiManager;
	//ターゲットマーカー
	std::unique_ptr<TargetMarker> m_targetMarker;
	//エフェクトマイクロソフト
	std::unique_ptr<EffectsManager> m_effectsManager;
	SceneManager::StageID m_stageID;

	//チュートリアル画像
	std::unique_ptr<UserInterface> m_tutorialTex;

	std::unique_ptr<Sky> m_sky;

	
	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;

	// シーンチェンジフラグ
	bool m_isChangeScene;
	//次のシーン
	SceneID m_nextScene;

	bool m_isTutolialTex;

	SoundManager* m_soundManager;

};
