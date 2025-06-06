/*
	鳥の敵のビームの攻撃
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

// BirdEnemyBeamAttackクラスを定義する
class BirdEnemyBeamAttack : public IState
{
public:
	// コンストラクタ
	BirdEnemyBeamAttack(BirdEnemy* birdEnemy, BirdEnemyBeam* beam);
	// デストラクタ
	~BirdEnemyBeamAttack() override;
	// 初期化する
	void Initialize() ;

	// 更新処理
	void Update(const float& elapsedTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override ;



private:

	//鳥の敵
	BirdEnemy* m_birdEnemy;
	//プレイヤ
	Player* m_player;
	//ビーム
	BirdEnemyBeam* m_beam;
	//動く方向
	DirectX::SimpleMath::Vector3 m_moveDirectiion;
	//初期のスピード
	float m_initialSpeed;
	//最終スピード
	float m_finalSpeed;
	//減速時間
	float m_decelerationTime;
	//時間
	float m_time;

};


