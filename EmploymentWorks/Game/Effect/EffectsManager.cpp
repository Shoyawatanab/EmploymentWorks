/*
	@file	EffectsManager.cpp
	@brief	
*/
#include "pch.h"
#include "EffectsManager.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include <cassert>

#include "Game/Effect/ExplosionEffects.h"
#include "Game/Effect/DamageVignette.h"
#include "Game/Observer/Messenger.h"
#include "Game/Effect/Particle/Particle.h"
#include "Game/Effect/HitEffect/HitEffect.h"

/// <summary>
/// コンストラクタ
/// </summary>
EffectsManager::EffectsManager()
	:
	m_commonResources{}
	, m_effects{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
EffectsManager::~EffectsManager()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void EffectsManager::Initialize(CommonResources* resources)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;



	for (int i = 0; i < 10; i++)
	{

		auto explosion = std::make_unique<ExplosionEffects>(m_commonResources);
		explosion->Initialize();

		m_effects.push_back(std::move(explosion));

	}

	//ダメージエフェクト
	auto damegeVignette = std::make_unique<DamageVignette>(m_commonResources);
	damegeVignette->Initialize();
	m_effects.push_back(std::move(damegeVignette));

	//
	auto particle = std::make_unique < Particle>(m_commonResources);
	particle->Initialize();

	m_effects.push_back(std::move(particle));
	
	particle = std::make_unique < Particle>(m_commonResources);
	particle->Initialize();

	m_effects.push_back(std::move(particle));


	for (int i = 0; i < 40; i++)
	{

		auto hit = std::make_unique<HitEffect>(m_commonResources);
		hit->Initialize();
		m_effects.push_back(std::move(hit));

	}



	Messenger::Attach(EventParams::EventType::PlayerDamage, this);
	Messenger::Attach(EventParams::EventType::CreateExplosion, this);
	Messenger::Attach(EventParams::EventType::CreateParticle, this);
	Messenger::Attach(EventParams::EventType::CreateHitEffect, this);

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void EffectsManager::Update(const float& elapsedTime)
{

	for (auto& effect : m_effects)
	{
		effect->Update(elapsedTime);
	}

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void EffectsManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	using namespace DirectX::SimpleMath;

	for (auto& effect : m_effects)
	{

		effect->Render(view, projection);


	}

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void EffectsManager::Finalize()
{
	// do nothing.
}

/// <summary>
/// 爆発の生成
/// </summary>
/// <param name="datas">データ</param>
void EffectsManager::CreateExploion(void* datas)
{

	EventParams::CreateExplosionDatas* data = static_cast<EventParams::CreateExplosionDatas*>(datas);

	//使えるエフェクトの取得
	auto it = std::find_if(
		m_effects.begin(), m_effects.end(),
		[](const std::unique_ptr<IEffect>& effect)
		{
			return effect->GetEffectType() == IEffect::EffectType::Explosion && !effect->GetIsActive();
		});

	//エフェクトがあれば
	if (it != m_effects.end())
	{
		(*it)->SetIsActive(true);
		(*it)->SetPosition(data->Position);
		(*it)->SetScale(data->Scale);
	}

}

/// <summary>
/// ダメージエフェクトの生成
/// </summary>
/// <param name="datas">データ</param>
void EffectsManager::CreatePlayerDamageEffect(void* datas)
{

	EventParams::CreateExplosionDatas* data = static_cast<EventParams::CreateExplosionDatas*>(datas);

	//使えるエフェクトの取得
	auto it = std::find_if(
		m_effects.begin(), m_effects.end(),
		[](const std::unique_ptr<IEffect>& effect)
		{
			return effect->GetEffectType() == IEffect::EffectType::PlayerDamage && !effect->GetIsActive();
		});

	//エフェクトがあれば
	if (it != m_effects.end())
	{
		(*it)->SetIsActive(true);

	}
}

/// <summary>
/// 煙エフェクトの生成
/// </summary>
/// <param name="datas">データ</param>
void EffectsManager::CreateParticle(void* datas)
{

	EventParams::CreateExplosionDatas* data = static_cast<EventParams::CreateExplosionDatas*>(datas);

	//使えるエフェクトの取得
	auto it = std::find_if(
		m_effects.begin(), m_effects.end(),
		[](const std::unique_ptr<IEffect>& effect)
		{
			return effect->GetEffectType() == IEffect::EffectType::Particle && !effect->GetIsActive();
		});

	//エフェクトがあれば
	if (it != m_effects.end())
	{
		
		(*it)->SetIsActive(true);
		(*it)->Create(datas);
	}


}
/// <summary>
/// ヒットエフェクトの生成
/// </summary>
/// <param name="datas">データ</param>
void EffectsManager::CreateHitEffect(void* datas)
{

	EventParams::CreateHitEffectDatas* data = static_cast<EventParams::CreateHitEffectDatas*>(datas);

	//使えるエフェクトの取得
	auto it = std::find_if(
		m_effects.begin(), m_effects.end(),
		[](const std::unique_ptr<IEffect>& effect)
		{
			return effect->GetEffectType() == IEffect::EffectType::HitEffect && !effect->GetIsActive();
		});

	//エフェクトがあれば
	if (it != m_effects.end())
	{

		(*it)->SetIsActive(true);
		(*it)->Create(datas);
	}


}
/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">イベントの種類</param>
/// <param name="datas">イベントのデータ</param>
void EffectsManager::Notify(EventParams::EventType type, void* datas)
{

	switch (type)
	{
		case EventParams::EventType::CreateExplosion:
			CreateExploion(datas);
			break;
		case EventParams::EventType::PlayerDamage:
			CreatePlayerDamageEffect(datas);
			break;
		case EventParams::EventType::CreateParticle:
			CreateParticle(datas);
			break;
		case EventParams::EventType::CreateHitEffect:
			CreateHitEffect(datas);
			break;
		default:
			break;
	}

}


