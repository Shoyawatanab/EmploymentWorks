#pragma once
#include <pch.h>
#include "Interface/IEnemyState.h"

class Enemy;

// EnemyAttackクラスを定義する
class EnemyAttack : public IEnemyState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// コンストラクタ
	EnemyAttack(Enemy* enemy);
	// デストラクタ
	~EnemyAttack();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

private:
	Enemy* m_enemy;

	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// バウンディングスフィア
	DirectX::BoundingSphere m_boundingSphereLeftLeg;

};

