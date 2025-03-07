/*
　鳥の敵の動き
*/
#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"
class CommonResources;

class Boomerang;
class Player;
class BirdEnemy;

// BirdEnemyMoveクラスを定義する
class BirdEnemyMove : public IState
{

public:
	// コンストラクタ
	BirdEnemyMove();
	// デストラクタ
	~BirdEnemyMove();
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

	DirectX::SimpleMath::Vector3 m_startPosition;

	DirectX::SimpleMath::Vector3 m_endPosition;

	float m_time;



};

