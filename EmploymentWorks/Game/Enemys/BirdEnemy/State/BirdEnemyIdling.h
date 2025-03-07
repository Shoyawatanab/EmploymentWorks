/*
* 鳥の敵の通常状態
*/
#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"
class CommonResources;

class Boomerang;
class Player;
class BirdEnemy;

// BirdEnemyldlingクラスを定義する
class BirdEnemyldling : public IState
{
public:
	// コンストラクタ
	BirdEnemyldling();
	// デストラクタ
	~BirdEnemyldling();
	// 初期化する
	void Initialize(CommonResources* resoure);

	// 更新する
	void Update(const float& elapsedTime);
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override ;

	void Enter();
	void Exit();

	//クラスに必要な情報（ポインタ）の登録
	void AddPointer(Player* player, BirdEnemy* birdEnemy);

private:

	// 共通リソース
	CommonResources* m_commonResources;

	BirdEnemy* m_birdEnemy;


	Player* m_player;


	float m_time;

	float m_attackInterval;


};

