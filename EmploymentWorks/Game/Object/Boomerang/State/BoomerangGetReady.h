#pragma once
#include <pch.h>
#include "Interface/IBoomerangState.h"

class Boomerang;
class Player;

// BoomerangGetReadyクラスを定義する
class BoomerangGetReady : public IBoomerangState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// コンストラクタ
	BoomerangGetReady();
	// デストラクタ
	~BoomerangGetReady();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//クラスに必要な情報（ポインタ）の登録
	void RegistrationInformation(Boomerang* boomerang, Player* player);


private:
	Boomerang* m_boomerang;

	Player* m_player;

	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// バウンディングスフィア
	DirectX::BoundingSphere m_boundingSphereLeftLeg;

};

