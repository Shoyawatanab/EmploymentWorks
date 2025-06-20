//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto
// <製作開始日>		2025/06/12
// <file>			Shapes.h
// <概要>		　　様々な形
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"ShapeBase.h"
#include"GameBase/Component/Particle/ParticleMath.h"

// 球++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 引数は float radius(半径)
class ShapeSphere : public ShapeBase
{
public:
	// コンストラクタ
	ShapeSphere(float radius , int thickness = 0);
	void Generate();

private:
	float m_radius = 1.0f;
	int m_thickness;
};

// 半球++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 引数は float radius(半径)
class ShapeHemiSphere : public ShapeBase
{
public:
	// コンストラクタ
	ShapeHemiSphere(float radius , const DirectX::SimpleMath::Vector3& direction , int thickeness = 0);
	void Generate();

private:
	float m_radius;
	DirectX::SimpleMath::Vector3 m_direction;
	int m_thickness;
};

// 箱++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 引数は Vector3 size(サイズ)
class ShapeBox : public ShapeBase
{
public:
	// コンストラクタ
	ShapeBox(const DirectX::SimpleMath::Vector3& size , int thickness = 0);
	void Generate();

private:
	DirectX::SimpleMath::Vector3 m_size = { 1 , 1, 1 };
	int m_thickness;
};

// コーン++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 引数は float radius(半径) , float angle(角度) , Vector3 direciton(向き)
class ShapeCone : public ShapeBase
{
public:
	// コンストラクタ
	ShapeCone(float radius, float angle , DirectX::SimpleMath::Vector3 direction);
	void Generate();

private:
	float m_radius;
	float m_angle;
	DirectX::SimpleMath::Vector3 m_direction;
	
};