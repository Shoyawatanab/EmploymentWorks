#pragma once
#include <pch.h>
#include "Interface/IBoomerangState.h"

class Boomerang;

// BoomerangDrop�N���X���`����
class BoomerangDrop : public IBoomerangState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// �R���X�g���N�^
	BoomerangDrop(Boomerang* boomerang );
	// �f�X�g���N�^
	~BoomerangDrop();
	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

private:
	Boomerang* m_boomerang;


	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;

};
