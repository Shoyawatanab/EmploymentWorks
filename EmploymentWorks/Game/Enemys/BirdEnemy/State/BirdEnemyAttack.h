/*
	鳥の敵の攻撃
*/
#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"

class CommonResources;

class Boomerang;
class Player;
class BirdEnemy;

// BirdEnemyAttackクラスを定義する
class BirdEnemyAttack : public IState
{
public:
	// コンストラクタ
	BirdEnemyAttack();
	// デストラクタ
	~BirdEnemyAttack();
	// 初期化する
	void Initialize(CommonResources* resoure);

	// 更新する
	void Update(const float& elapsedTime);
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	void Enter();
	void Exit();

	//クラスに必要な情報（ポインタ）の登録
	void AddPointer(Player* player, BirdEnemy* birdEnemy);



private:

	// 共通リソース
	CommonResources* m_commonResources;

	BirdEnemy* m_birdEnemy;


	Player* m_player;
	//溜め時間
	float m_accumulationTime;

	float m_shotTime;

	//打つ玉の数
	int m_bulletCount;

};

