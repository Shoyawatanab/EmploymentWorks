#pragma once
/*
	@file	EnemyManager.h.h
	@brief	敵の管理クラス
*/
#pragma once
#include "pch.h"
#include "Game/Entities/EnemyEntity.h"
#include "Libraries/WataLib/Json.h"
#include "Game/Observer/Messenger.h"

// 前方宣言
class CommonResources;
class Player;
class BossEnemy;
class StageObjectManager;

class EnemyManager 
{
public:
	//ボステキの取得
	BossEnemy* GetBossEnemy() { return m_bossEnemy; }

	//ボスのHP割合の取得
	float GetBossHPRation();
	//すべての敵情報の取得
	std::vector<std::unique_ptr<EnemyEntity>>& GetEnemys() { return m_enemys; }


public:
	//コンストラクタ
	EnemyManager(Player* player, StageObjectManager* stageObjectmanger);
	//デストラクタ
	~EnemyManager() ;
	//初期化
	void Initialize(CommonResources* resources);
	//更新処理
	void Update(const float& elapsedTime);
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) ;
	//
	void Finalize() ;
	//敵情報の追加
	void AddEnemyData(WataLib::Json::ObjectData enemyData);

	//当たり判定クラスに登録
	void  AddCollision(CollisionManager* collsionManager);


	//最後の敵の取得
	EnemyEntity* GetLastEnemy() { return m_remainingEnemys[0]; }

	//残っている敵の削除
	void DeleteRemainingEnemy(EnemyEntity* character) 
	{

		if (m_remainingEnemys.size() <= 1) {
			Messenger::GetInstance()->Notify(GameMessageType::GAME_CLEAR, nullptr);
			Messenger::GetInstance()->Notify(GameMessageType::DEFEATED_All_ENEMIES, nullptr);
			return;
		}

		// 指定されたキャラクターを探して削除
		auto it = std::find(m_remainingEnemys.begin(), m_remainingEnemys.end(), character);
		if (it != m_remainingEnemys.end()) {
			m_remainingEnemys.erase(it); // 見つかった場合は削除
		}
	}






private:

	void CreateEnemy();

private:
	// 共通リソース
	CommonResources* m_commonResources;
	//敵配列
	std::vector<std::unique_ptr<EnemyEntity>> m_enemys;
	//残りの敵
	std::vector<EnemyEntity*> m_remainingEnemys;
	//プレイヤ
	Player* m_player;
	//ステージオブジェクトマネージャー
	StageObjectManager* m_stageObjectmanger;
	//ボス敵
	BossEnemy* m_bossEnemy;
	//敵情報
	std::vector<WataLib::Json::ObjectData> m_enemyDatas;


};
