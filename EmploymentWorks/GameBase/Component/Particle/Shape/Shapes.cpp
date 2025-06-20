//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto
// <����J�n��>		2025/06/12
// <file>			Shapes.cpp
// <�T�v>		�@�@�l�X�Ȍ`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Shapes.h"

// ��+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="radius">���a</param>
ShapeSphere::ShapeSphere(float radius , int thickness)
	:
	m_radius{radius},
	m_thickness{thickness}
{

}

/// <summary>
/// ��������
/// </summary>
void ShapeSphere::Generate()
{
	// �����̐���
	auto dir = ParticleMath::RandomUnitVector();
	if (m_thickness == 0)
	{
		m_position = dir * m_radius;
	}
	else
	{
		m_position = DirectX::SimpleMath::Vector3::Zero;
	}
	
	m_velocity = dir * m_radius;
}

// ����++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="radius">���a</param>
/// <param name="direction">���������</param>
ShapeHemiSphere::ShapeHemiSphere(float radius, const DirectX::SimpleMath::Vector3& direction, int thickness)
	:
	m_radius{radius},
	m_direction{direction},
	m_thickness{ thickness }
{

}

/// <summary>
/// ��������
/// </summary>
/// <param name="baseVelocity"></param>
void ShapeHemiSphere::Generate()
{
	auto dir = ParticleMath::RandomHemiSphereVector(m_direction);
	if (m_thickness == 0)
	{
		m_position = dir * m_radius;
	}
	else
	{
		auto len = ParticleMath::RandomRange(0.0f, m_radius);
		m_position = dir * len;
	}
	m_velocity = dir * m_radius;
}



// ��++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="size">�傫��</param>
ShapeBox::ShapeBox(const DirectX::SimpleMath::Vector3& size, int thickness)
	:
	m_size{size},
	m_thickness{ thickness }
{

}
/// <summary>
/// ��������
/// </summary>
void ShapeBox::Generate()
{
	if (m_thickness == 0)
	{
		auto face = ParticleMath::RandomRange(0, 5);
		auto pos = ParticleMath::RandomRange(-m_size * 0.5f, m_size * 0.5f);
		switch (face)
		{
		case 0: pos.x = -m_size.x * 0.5f; break;
		case 1: pos.x = m_size.x * 0.5f; break;
		case 2: pos.y = -m_size.y * 0.5f; break;
		case 3: pos.y = m_size.y * 0.5f; break;
		case 4: pos.z = -m_size.z * 0.5f; break;
		case 5: pos.z = m_size.z * 0.5f; break;
		}
		m_position = pos;
	}
	else
	{
		m_position = ParticleMath::RandomRange(-m_size * 0.5f, m_size * 0.5f);
	}
	m_velocity = DirectX::SimpleMath::Vector3::Up;
}

// �R�[��++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="radius">���a</param>
/// <param name="angle">�p�x</param>
/// <param name="direction">����</param>
ShapeCone::ShapeCone(float radius, float angle, DirectX::SimpleMath::Vector3 direction)
	:
	m_radius{radius},
	m_angle{angle},
	m_direction{direction}
{

}

/// <summary>
/// ��������
/// </summary>
void ShapeCone::Generate()
{
	auto dir = ParticleMath::RandomConeVector(m_direction, DirectX::XMConvertToRadians(m_angle));
	m_position = DirectX::SimpleMath::Vector3::Zero;
	m_velocity = dir;
}