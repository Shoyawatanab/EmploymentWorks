//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto
// <製作開始日>		2025/06/12
// <file>			ShapeBase.cpp
// <概要>		　　形状のベース
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"GameBase/Component/Particle/ParticleUtility.h"

class ShapeBase
{
public:
	// デストラクタ
	virtual ~ShapeBase() = default;
	// 位置、速度を決定し、生成する関数
	virtual void Generate() = 0;

	// 位置、速度取得用
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	DirectX::SimpleMath::Vector3 GetVelocity() { return m_velocity; }

protected:
	// 位置、速度
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_velocity;
};