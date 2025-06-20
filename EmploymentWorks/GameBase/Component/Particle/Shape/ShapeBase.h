//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto
// <����J�n��>		2025/06/12
// <file>			ShapeBase.cpp
// <�T�v>		�@�@�`��̃x�[�X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"GameBase/Component/Particle/ParticleUtility.h"

class ShapeBase
{
public:
	// �f�X�g���N�^
	virtual ~ShapeBase() = default;
	// �ʒu�A���x�����肵�A��������֐�
	virtual void Generate() = 0;

	// �ʒu�A���x�擾�p
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	DirectX::SimpleMath::Vector3 GetVelocity() { return m_velocity; }

protected:
	// �ʒu�A���x
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_velocity;
};