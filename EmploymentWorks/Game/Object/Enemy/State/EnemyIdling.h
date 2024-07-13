#pragma once
#include <pch.h>
#include "Interface/IEnemyState.h"

class Boomerang;
class Player;

// EnemyIdlingクラスを定義する
class EnemyIdling : public IEnemyState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// コンストラクタ
	EnemyIdling();
	// デストラクタ
	~EnemyIdling();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

private:
	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// バウンディングスフィア
	DirectX::BoundingSphere m_boundingSphereLeftLeg;

};

