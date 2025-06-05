/*
	鳥の敵のビームの通常状態
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

// BirdEnemyBeamIdlingクラスを定義する
class BirdEnemyBeamIdling : public IState
{
public:
	// コンストラクタ
	BirdEnemyBeamIdling(BirdEnemy* birdEnemy, BirdEnemyBeam* beam);
	// デストラクタ
	~BirdEnemyBeamIdling() override;
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime) override ;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit()override ;


private:

	//鳥の敵
	BirdEnemy* m_birdEnemy;
	//プレイヤ
	Player* m_player;
	//ビーム
	BirdEnemyBeam* m_beam;

};

