#pragma once
#include <pch.h>
#include "Interface/IBoomerangState.h"

class Boomerang;
class Player;

// BoomerangGetReady�N���X���`����
class BoomerangGetReady : public IBoomerangState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// �R���X�g���N�^
	BoomerangGetReady(Boomerang* boomerang , Player* player);
	// �f�X�g���N�^
	~BoomerangGetReady();
	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

private:
	Boomerang* m_boomerang;

	Player* m_player;

	// �f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* m_context;
	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �o�E���f�B���O�X�t�B�A
	DirectX::BoundingSphere m_boundingSphereLeftLeg;

};
