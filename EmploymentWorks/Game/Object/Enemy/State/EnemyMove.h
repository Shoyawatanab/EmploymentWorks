#pragma once
#include <pch.h>
#include "Interface/IEnemyState.h"
class Enemy;

// EnemyMoveクラスを定義する
class EnemyMove : public IEnemyState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// コンストラクタ
	EnemyMove(Enemy* enemy);
	// デストラクタ
	~EnemyMove();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void ChangePos();

	void Enter();
	void Exit();

private:
	Enemy* m_enemy;

	float m_lerpT;
	float m_acceleration;
	DirectX::SimpleMath::Vector3 m_startPos[3];
	DirectX::SimpleMath::Vector3 m_endPos[3];
	int m_index;
	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// バウンディングスフィア
	DirectX::BoundingSphere m_boundingSphereLeftLeg;

};

