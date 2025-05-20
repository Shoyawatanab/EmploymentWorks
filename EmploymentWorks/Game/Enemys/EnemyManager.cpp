/*
	@file	EnemyManager.cpp
	@brief	
*/
#include "pch.h"
#include "EnemyManager.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include <cassert>
#include "Game/CollisiionManager.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"
#include "Game/Params.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤ</param>
/// <param name="stageObjectmanger">ステージオブジェクトマネージャー</param>
EnemyManager::EnemyManager(Player* player, StageObjectManager* stageObjectmanger)
	:
	m_commonResources{}
	,m_enemys{}
	,m_remainingEnemys{}
	,m_player{player}
	,m_bossEnemy{}
	,m_enemyDatas{}
	,m_stageObjectmanger{stageObjectmanger}
{

}

/// <summary>
/// デストラクタ
/// </summary>
EnemyManager::~EnemyManager()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void EnemyManager::Initialize(CommonResources* resources)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;

	//敵の生成
	CreateEnemy();

	//残りの敵の変数に代入
	for (auto& enemy : m_enemys)
	{
		m_remainingEnemys.push_back(enemy.get());
	}
	
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void EnemyManager::Update(const float& elapsedTime)
{
	//敵の更新
	for (auto& enemy : m_enemys)
	{
		enemy->Update(elapsedTime);
	}

}


/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void EnemyManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	using namespace DirectX::SimpleMath;

	//敵の描画
	for (auto& enemy : m_enemys)
	{
		enemy->Render(view, projection);
	}

}

void EnemyManager::Finalize()
{
	// do nothing.
}



/// <summary>
/// 敵の生成
/// </summary>
void EnemyManager::CreateEnemy()
{
	for (auto& enemyData : m_enemyDatas)
	{
		//敵の種類
		std::string kind = enemyData.ModelName;


		if (kind == "BossEnemy")
		{
			auto enemy = std::make_unique<BossEnemy>(m_commonResources
				, enemyData.Scale, enemyData.Position,
				DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
					DirectX::XMConvertToRadians(enemyData.Rotation.y),
					DirectX::XMConvertToRadians(enemyData.Rotation.x),
					DirectX::XMConvertToRadians(enemyData.Rotation.z))
			);
			enemy->SetManager(this);
			enemy->AddPointer(m_player,m_stageObjectmanger);
			enemy->Initialize();

			m_bossEnemy = enemy.get();

			m_enemys.push_back(std::move(enemy));

		}
		else if (kind == "BirdEnemy")
		{
			auto enemy = std::make_unique<BirdEnemy>(m_commonResources
			, enemyData.Scale, enemyData.Position, 
				DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
					DirectX::XMConvertToRadians(enemyData.Rotation.y),
					DirectX::XMConvertToRadians(enemyData.Rotation.x),
					DirectX::XMConvertToRadians(enemyData.Rotation.z))
			);
			enemy->SetManager(this);
			enemy->AddPointer(m_player);
			enemy->Initialize();


			m_enemys.push_back(std::move(enemy));
		}

	}


}

/// <summary>
/// 敵データの追加
/// </summary>
/// <param name="enemyData">データ</param>
void EnemyManager::AddEnemyData(WataLib::Json::StageData enemyData)
{

	m_enemyDatas.push_back(enemyData);

}

/// <summary>
/// 当たり判定クラスに追加
/// </summary>
/// <param name="collsionManager">当たり判定クラス</param>
void EnemyManager::AddCollision(CollisionManager* collsionManager)
{
	for (auto& enemy : m_enemys)
	{
		enemy->AddCollision(collsionManager);
	}
}


/// <summary>
/// ボスのHP割合の取得
/// </summary>
/// <returns>割合</returns>
float EnemyManager::GetBossHPRation()
{
	//割合を求める
	float ration = m_bossEnemy->GetHP() / static_cast<float>(Params::BOSSENEMY_MAX_HP);
	return ration;
}


