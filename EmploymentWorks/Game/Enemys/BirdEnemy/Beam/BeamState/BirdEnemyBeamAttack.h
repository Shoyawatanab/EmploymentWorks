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
	BirdEnemyBeamAttack(Player* player, BirdEnemy* birdEnemy, BirdEnemyBeam* beam);
	// デストラクタ
	~BirdEnemyBeamAttack();
	// 初期化する
	void Initialize(CommonResources* resoure);

	// 更新処理
	void Update(const float& elapsedTime);
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) ;
	//状態に入った時
	void Enter();
	//状態を抜けた時
	void Exit();



private:

	// 共通リソース
	CommonResources* m_commonResources;
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


