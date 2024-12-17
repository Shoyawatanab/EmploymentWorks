#pragma once
#include <pch.h>
#include "Interface/IBirdEnemyState.h"
class CommonResources;

class Boomerang;
class Player;
class BirdEnemy;

// BirdEnemyldlingクラスを定義する
class BirdEnemyldling : public IBirdEnemyState
{
public:




	void SetResouces(CommonResources* resoure) { m_commonResources = resoure; }

public:
	// コンストラクタ
	BirdEnemyldling();
	// デストラクタ
	~BirdEnemyldling();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//クラスに必要な情報（ポインタ）の登録
	void RegistrationInformation(CommonResources* resoure, Player* player, BirdEnemy* birdEnemy);


private:

private:

	// 共通リソース
	CommonResources* m_commonResources;

	BirdEnemy* m_birdEnemy;


	Player* m_player;



	float m_graivty;


};

