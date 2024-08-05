#pragma once
#include <pch.h>
#include "Interface/IEnemyState.h"

class Enemy;

// EnemyAttack�N���X���`����
class EnemyAttack : public IEnemyState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// �R���X�g���N�^
	EnemyAttack(Enemy* enemy);
	// �f�X�g���N�^
	~EnemyAttack();
	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

private:
	Enemy* m_enemy;

	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �o�E���f�B���O�X�t�B�A
	DirectX::BoundingSphere m_boundingSphereLeftLeg;

};

