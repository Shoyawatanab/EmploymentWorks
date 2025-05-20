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
	BirdEnemyBeamIdling(Player* player, BirdEnemy* birdEnemy, BirdEnemyBeam* beam);
	// デストラクタ
	~BirdEnemyBeamIdling();
	// 初期化する
	void Initialize(CommonResources* resoure);

	// 更新する
	void Update(const float& elapsedTime);
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
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

};

