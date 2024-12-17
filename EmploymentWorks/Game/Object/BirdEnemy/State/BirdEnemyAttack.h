#pragma once
#include <pch.h>
#include "Interface/IBirdEnemyState.h"
class CommonResources;

class Boomerang;
class Player;
class BirdEnemy;

// BirdEnemyAttackクラスを定義する
class BirdEnemyAttack : public IBirdEnemyState
{
public:



	void SetResouces(CommonResources* resoure) { m_commonResources = resoure; }

public:
	// コンストラクタ
	BirdEnemyAttack();
	// デストラクタ
	~BirdEnemyAttack();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//クラスに必要な情報（ポインタ）の登録
	void RegistrationInformation(CommonResources* resoure, Player* player, BirdEnemy* birdEnemy);


private:
	void Attack(float elapsedTime, DirectX::Keyboard::State key);

private:

	// 共通リソース
	CommonResources* m_commonResources;
	BirdEnemy* m_birdEnemy;

	Player* m_player;

	float m_graivty;


};

