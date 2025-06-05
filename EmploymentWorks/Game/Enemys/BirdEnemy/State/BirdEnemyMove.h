/*
　鳥の敵の動き
*/
#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"
//前方宣言
class CommonResources;
class Boomerang;
class Player;
class BirdEnemy;

// BirdEnemyMoveクラスを定義する
class BirdEnemyMove : public IState
{

public:
	// コンストラクタ
	BirdEnemyMove(BirdEnemy* owner);
	// デストラクタ
	~BirdEnemyMove();
	// 初期化
	void Initialize();

	// 更新処理
	void Update(const float& elapsedTime);

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
	//初めの座標
	DirectX::SimpleMath::Vector3 m_startPosition;
	//終わりの座標
	DirectX::SimpleMath::Vector3 m_endPosition;
	//時間
	float m_time;



};

