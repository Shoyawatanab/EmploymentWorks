#pragma once
#include <pch.h>
#include "Interface/IBoomerangState.h"

class Boomerang;
class Player;

// BoomerangIdlingクラスを定義する
class BoomerangIdling : public IBoomerangState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// コンストラクタ
	BoomerangIdling(Boomerang* boomerang , Player* player);
	// デストラクタ
	~BoomerangIdling();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

private:
	Boomerang* m_boomerang;

	Player* m_player;

	// デバイスコンテキスト
	ID3D11DeviceContext* m_context;
	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// バウンディングスフィア
	DirectX::BoundingSphere m_boundingSphereLeftLeg;

};

