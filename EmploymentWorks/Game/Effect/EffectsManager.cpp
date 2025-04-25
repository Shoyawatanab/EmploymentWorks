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
#include "Game/Effect/ChargeEffect/ChargeEffect.h"

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

	auto chargeEffect = std::make_unique<ChargeEffect>(m_commonResources);
	chargeEffect->Initialize();

	m_effects.push_back(std::move(chargeEffect));

	Messenger::GetInstance()->Attach(MessageType::PlayerDamage, this);
	Messenger::GetInstance()->Attach(MessageType::CreateExplosion, this);
	Messenger::GetInstance()->Attach(MessageType::CreateParticle, this);
	Messenger::GetInstance()->Attach(MessageType::CreateHitEffect, this);
	Messenger::GetInstance()->Attach(MessageType::CreateChageEffect, this);

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

	UnknownDataTwo* data = static_cast<UnknownDataTwo*>(datas);

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
		(*it)->SetPosition(*static_cast<DirectX::SimpleMath::Vector3*>(data->data1));
		(*it)->SetScale(*static_cast<DirectX::SimpleMath::Vector3*>(data->data2));
	}

}

/// <summary>
/// ダメージエフェクトの生成
/// </summary>
/// <param name="datas">データ</param>
void EffectsManager::CreatePlayerDamageEffect(void* datas)
{
	UNREFERENCED_PARAMETER(datas);

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
	UNREFERENCED_PARAMETER(datas);

	//CreateExplosionDatas* data = static_cast<CreateExplosionDatas*>(datas);

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
	UNREFERENCED_PARAMETER(datas);

	//CreateHitEffectDatas* data = static_cast<CreateHitEffectDatas*>(datas);

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
void EffectsManager::CreateChargeEffect(void* datas)
{
	UNREFERENCED_PARAMETER(datas);

	//CreateChargeEffectDatas* data = static_cast<CreateChargeEffectDatas*>(datas);

	//使えるエフェクトの取得
	auto it = std::find_if(
		m_effects.begin(), m_effects.end(),
		[](const std::unique_ptr<IEffect>& effect)
		{
			return effect->GetEffectType() == IEffect::EffectType::ChargeEffect && !effect->GetIsActive();
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
void EffectsManager::Notify(const Telegram& telegram)
{

	switch (telegram.messageType)
	{
		case MessageType::CreateExplosion:
			CreateExploion(telegram.extraInfo);
			break;
		case MessageType::PlayerDamage:
			CreatePlayerDamageEffect(telegram.extraInfo);
			break;
		case MessageType::CreateParticle:
			CreateParticle(telegram.extraInfo);
			break;
		case MessageType::CreateHitEffect:
			//CreateHitEffect(datas);
			break;
		case MessageType::CreateChageEffect:
			CreateChargeEffect(telegram.extraInfo);
			break;
		default:
			break;
	}

}


