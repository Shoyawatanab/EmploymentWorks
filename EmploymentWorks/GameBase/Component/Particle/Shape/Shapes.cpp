//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto
// <製作開始日>		2025/06/12
// <file>			Shapes.cpp
// <概要>		　　様々な形
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"Shapes.h"

// 球+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="radius">半径</param>
ShapeSphere::ShapeSphere(float radius , int thickness)
	:
	m_radius{radius},
	m_thickness{thickness}
{

}

/// <summary>
/// 生成する
/// </summary>
void ShapeSphere::Generate()
{
	// 向きの生成
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

// 半球++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="radius">半径</param>
/// <param name="direction">上向き方向</param>
ShapeHemiSphere::ShapeHemiSphere(float radius, const DirectX::SimpleMath::Vector3& direction, int thickness)
	:
	m_radius{radius},
	m_direction{direction},
	m_thickness{ thickness }
{

}

/// <summary>
/// 生成する
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



// 箱++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="size">大きさ</param>
ShapeBox::ShapeBox(const DirectX::SimpleMath::Vector3& size, int thickness)
	:
	m_size{size},
	m_thickness{ thickness }
{

}
/// <summary>
/// 生成する
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

// コーン++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="radius">半径</param>
/// <param name="angle">角度</param>
/// <param name="direction">向き</param>
ShapeCone::ShapeCone(float radius, float angle, DirectX::SimpleMath::Vector3 direction)
	:
	m_radius{radius},
	m_angle{angle},
	m_direction{direction}
{

}

/// <summary>
/// 生成する
/// </summary>
void ShapeCone::Generate()
{
	auto dir = ParticleMath::RandomConeVector(m_direction, DirectX::XMConvertToRadians(m_angle));
	m_position = DirectX::SimpleMath::Vector3::Zero;
	m_velocity = dir;
}