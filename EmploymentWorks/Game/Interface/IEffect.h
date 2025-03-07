/*
* ステーとパターンのインターフェース
*/
#pragma once
#include "pch.h"

class CommonResources;

class IEffect
{
public:

	enum  class EffectType
	{

		Explosion
		,PlayerDamage
		,Particle
		, HitEffect

	};

public:
	//デストラクタ
	virtual ~IEffect() = default;
	// 初期化する
	virtual void Initialize() = 0;
	// 更新する
	virtual void Update(const float& elapsedTime) = 0;
	//描画
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) = 0;

	virtual bool GetIsActive() = 0;

	virtual void SetIsActive(bool isActive) = 0;

	virtual EffectType GetEffectType() = 0;

	virtual void SetPosition(DirectX::SimpleMath::Vector3 position) = 0;

	virtual void SetScale(DirectX::SimpleMath::Vector3 scale) = 0;

	virtual void Create(void* datas) = 0;
};
