/*
	鳥の敵のビームの/予備動作クラス
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



// BirdEnemyBeamPreliminaryActionクラスを定義する
class BirdEnemyBeamPreliminaryAction : public IState
{
public:
	// コンストラクタ
	BirdEnemyBeamPreliminaryAction(BirdEnemy* birdEnemy, BirdEnemyBeam* beam);
	// デストラクタ
	~BirdEnemyBeamPreliminaryAction() override;
	// 初期化する
	void Initialize();

	// 更新処理
	void Update(const float& elapsedTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;


private:

	//鳥の敵
	BirdEnemy* m_birdEnemy;
	//プレイヤ
	Player* m_player;
	//ビーム
	BirdEnemyBeam* m_beam;
	//時間
	float m_time;

};

