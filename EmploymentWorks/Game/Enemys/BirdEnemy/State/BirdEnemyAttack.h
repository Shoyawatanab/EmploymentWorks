/*
	鳥の敵の攻撃
*/
#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"

//前方宣言
class CommonResources;
class Boomerang;
class Player;
class BirdEnemy;
class BirdEnemyBeam;

// BirdEnemyAttackクラスを定義する
class BirdEnemyAttack : public IState
{
public:
	// コンストラクタ
	BirdEnemyAttack(BirdEnemy* owner, std::vector<std::unique_ptr<BirdEnemyBeam>>& beams);
	// デストラクタ
	~BirdEnemyAttack();
	// 初期化
	void Initialize();

	// 更新処理
	void Update(const float& elapsedTime);
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
	//状態に入った時
	void Enter();
	//状態を抜けた時
	void Exit();


private:

	//鳥の敵
	BirdEnemy* m_birdEnemy;
	//プレイヤ
	Player* m_player;
	//溜め時間
	float m_accumulationTime;
	//撃つ時間
	float m_shotTime;

	//打つ玉の数
	int m_bulletCount;


	std::vector<std::unique_ptr<BirdEnemyBeam>>& m_beams;

};

