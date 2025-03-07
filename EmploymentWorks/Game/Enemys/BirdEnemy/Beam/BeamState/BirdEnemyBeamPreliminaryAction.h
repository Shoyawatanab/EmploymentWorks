/*
	鳥の敵のビームの溜め
*/
#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"
class CommonResources;

class Boomerang;
class Player;
class BirdEnemy;
class BirdEnemyBeam;

//予備動作クラス

// BirdEnemyBeamPreliminaryActionクラスを定義する
class BirdEnemyBeamPreliminaryAction : public IState
{
public:
	// コンストラクタ
	BirdEnemyBeamPreliminaryAction(Player* player, BirdEnemy* birdEnemy, BirdEnemyBeam* beam);
	// デストラクタ
	~BirdEnemyBeamPreliminaryAction();
	// 初期化する
	void Initialize(CommonResources* resoure);

	// 更新する
	void Update(const float& elapsedTime);
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	void Enter();
	void Exit();


private:

	// 共通リソース
	CommonResources* m_commonResources;

	BirdEnemy* m_birdEnemy;


	Player* m_player;


	BirdEnemyBeam* m_beam;

	float m_time;

};

