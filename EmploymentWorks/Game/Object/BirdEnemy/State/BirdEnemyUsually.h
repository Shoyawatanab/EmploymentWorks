#pragma once
#include <pch.h>
#include "Interface/IBirdEnemyState.h"
class CommonResources;

class Boomerang;
class Player;
class BirdEnemy;

// BirdEnemyUsuallyクラスを定義する
class BirdEnemyUsually : public IBirdEnemyState
{
public:



	void SetResouces(CommonResources* resoure) { m_commonResources = resoure; }

public:
	// コンストラクタ
	BirdEnemyUsually();
	// デストラクタ
	~BirdEnemyUsually();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//クラスに必要な情報（ポインタ）の登録
	void RegistrationInformation(CommonResources* resoure,Player* player,BirdEnemy* birdEnemy);


private:
	void Move(float elapsedTime,  DirectX::SimpleMath::Vector3 moveDirection);
	void Rotate(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection);

private:

	// 共通リソース
	CommonResources* m_commonResources;

	BirdEnemy* m_birdEnemy;

	Player* m_player;





};

