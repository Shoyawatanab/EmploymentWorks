#pragma once
#include <pch.h>
#include "Interface/IEnemyState.h"
class Boomerang;
class Player;

// EnemyMove�N���X���`����
class EnemyMove : public IEnemyState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// �R���X�g���N�^
	EnemyMove();
	// �f�X�g���N�^
	~EnemyMove();
	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

private:

	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �o�E���f�B���O�X�t�B�A
	DirectX::BoundingSphere m_boundingSphereLeftLeg;

};

