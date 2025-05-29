/*
* 鳥の敵の通常状態
*/
#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"

//前方宣言
class CommonResources;
class Boomerang;
class Player;
class BirdEnemy;

// BirdEnemyldlingクラスを定義する
class BirdEnemyldling : public IState
{
public:
	// コンストラクタ
	BirdEnemyldling(BirdEnemy* owner);
	// デストラクタ
	~BirdEnemyldling();
	// 初期化
	void Initialize()  ;

	// 更新処理
	void Update(const float& elapsedTime);
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override ;
	//状態に入った時
	void Enter();
	//状態を抜けた時
	void Exit();

private:

	//鳥の敵
	BirdEnemy* m_birdEnemy;
	//プレイヤ
	Player* m_player;
	//時間
	float m_time;
	//インターバル
	float m_attackInterval;


};

