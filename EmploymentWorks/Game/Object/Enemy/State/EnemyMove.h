#pragma once
#include <pch.h>
#include "Interface/IEnemyState.h"
class Boomerang;
class Player;

// EnemyMoveクラスを定義する
class EnemyMove : public IEnemyState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// コンストラクタ
	EnemyMove();
	// デストラクタ
	~EnemyMove();
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

