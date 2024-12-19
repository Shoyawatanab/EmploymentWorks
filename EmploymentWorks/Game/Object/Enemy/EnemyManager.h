/*
	@file	EnemyManager.h
	@brief	シーンマネージャクラス
*/
#pragma once
#include "Game/Object/BirdEnemy/BirdEnemyBase.h"

// 前方宣言
class CommonResources;
class Fade;
class Player;

class EnemyManager
{

private:
	CommonResources* m_commonResources;

	std::vector<std::unique_ptr<BirdEnemyBase>> m_enemys;

public:
	EnemyManager();
	~EnemyManager();

	void Initialize();
	void Update(float elapsedTime);
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
	void Finalize();



	//クラスのインスタンス
	void Instances(Player* player, CommonResources* resources);


};

//ボスは入れずに雑魚敵だけを一旦管理する