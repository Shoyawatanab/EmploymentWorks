//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto
// <����J�n��>		2025/06/12
// <file>			Shapes.h
// <�T�v>		�@�@�l�X�Ȍ`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"ShapeBase.h"
#include"GameBase/Component/Particle/ParticleMath.h"

// ��++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ������ float radius(���a)
class ShapeSphere : public ShapeBase
{
public:
	// �R���X�g���N�^
	ShapeSphere(float radius , int thickness = 0);
	void Generate();

private:
	float m_radius = 1.0f;
	int m_thickness;
};

// ����++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ������ float radius(���a)
class ShapeHemiSphere : public ShapeBase
{
public:
	// �R���X�g���N�^
	ShapeHemiSphere(float radius , const DirectX::SimpleMath::Vector3& direction , int thickeness = 0);
	void Generate();

private:
	float m_radius;
	DirectX::SimpleMath::Vector3 m_direction;
	int m_thickness;
};

// ��++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ������ Vector3 size(�T�C�Y)
class ShapeBox : public ShapeBase
{
public:
	// �R���X�g���N�^
	ShapeBox(const DirectX::SimpleMath::Vector3& size , int thickness = 0);
	void Generate();

private:
	DirectX::SimpleMath::Vector3 m_size = { 1 , 1, 1 };
	int m_thickness;
};

// �R�[��++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ������ float radius(���a) , float angle(�p�x) , Vector3 direciton(����)
class ShapeCone : public ShapeBase
{
public:
	// �R���X�g���N�^
	ShapeCone(float radius, float angle , DirectX::SimpleMath::Vector3 direction);
	void Generate();

private:
	float m_radius;
	float m_angle;
	DirectX::SimpleMath::Vector3 m_direction;
	
};