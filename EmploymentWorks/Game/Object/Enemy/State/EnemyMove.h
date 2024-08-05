#pragma once
#include <pch.h>
#include "Interface/IEnemyState.h"
class Enemy;

// EnemyMove�N���X���`����
class EnemyMove : public IEnemyState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// �R���X�g���N�^
	EnemyMove(Enemy* enemy);
	// �f�X�g���N�^
	~EnemyMove();
	// ����������
	void Initialize();

	// �X�V����
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
	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �o�E���f�B���O�X�t�B�A
	DirectX::BoundingSphere m_boundingSphereLeftLeg;

};

