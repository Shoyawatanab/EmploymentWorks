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
EffectsManager::EffectsManager(CommonResources* resources)
	:
	m_commonResources{resources}
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
void EffectsManager::Initialize()
{
	using namespace DirectX::SimpleMath;

	//各エフェクトの作成
	CreateEffect();

	//メッセージクラスに登録
	Messenger::GetInstance()->Rigister(GamePlayMessageType::PLAYER_DAMAGE, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::CREATE_EXPLOSION, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::CREATE_PARTICLE, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::CREATE_HIT_EFFECT, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::CREATE_CHAGE_EFFECT, this);

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void EffectsManager::Update(const float& elapsedTime)
{
	//エフェクトの更新
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

	//エフェクトの描画
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
	//データの取得
	UnknownDataTwo* data = static_cast<UnknownDataTwo*>(datas);

	//使えるエフェクトの取得
	auto it = std::find_if(
		m_effects.begin(), m_effects.end(),
		[](const std::unique_ptr<IEffect>& effect)
		{
			return effect->GetEffectType() == IEffect::EffectType::EXPLOSION && !effect->GetIsActive();
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
			return effect->GetEffectType() == IEffect::EffectType::PLAYER_DAMAGE && !effect->GetIsActive();
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
			return effect->GetEffectType() == IEffect::EffectType::PARTICLE && !effect->GetIsActive();
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
			return effect->GetEffectType() == IEffect::EffectType::HIT_EFFECT && !effect->GetIsActive();
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
			return effect->GetEffectType() == IEffect::EffectType::CHARGE_EFFECT && !effect->GetIsActive();
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
void EffectsManager::Notify(const Telegram<GamePlayMessageType>& telegram)
{

	switch (telegram.messageType)
	{
		//爆発の生成
		case GamePlayMessageType::CREATE_EXPLOSION:
			CreateExploion(telegram.extraInfo);
			break;
		//プレイヤのダメージエフェクトの生成
		case GamePlayMessageType::PLAYER_DAMAGE:
			CreatePlayerDamageEffect(telegram.extraInfo);
			break;
		//パーティクルエフェクトの生成
		case GamePlayMessageType::CREATE_PARTICLE:
			CreateParticle(telegram.extraInfo);
			break;
		//ヒットエフェクトの生成
		case GamePlayMessageType::CREATE_HIT_EFFECT:
			//CreateHitEffect(datas);
			break;
		//チャージエフェクトの生成
		case GamePlayMessageType::CREATE_CHAGE_EFFECT:
			CreateChargeEffect(telegram.extraInfo);
			break;
		default:
			break;
	}

}

/// <summary>
/// エフェクトの作成
/// </summary>
void EffectsManager::CreateEffect()
{

	//爆発エフェクト
	for (int i = 0; i < EXPLOION_EFFECT_COUNT; i++)
	{
		auto explosion = std::make_unique<ExplosionEffects>(m_commonResources);
		explosion->Initialize();

		m_effects.push_back(std::move(explosion));
	}

	//ダメージエフェクト
	auto damegeVignette = std::make_unique<DamageVignette>(m_commonResources);
	damegeVignette->Initialize();
	m_effects.push_back(std::move(damegeVignette));

	//パーティクルエフェクト
	for (int i = 0; i < PARTICLE_EFFECT_COUNT;i++)
	{
		auto particle = std::make_unique < Particle>(m_commonResources);
		particle->Initialize();

		m_effects.push_back(std::move(particle));

		particle = std::make_unique < Particle>(m_commonResources);
		particle->Initialize();

		m_effects.push_back(std::move(particle));

	}


	//ヒットエフェクト
	for (int i = 0; i < HIT_EFFECT_COUNT; i++)
	{
		auto hit = std::make_unique<HitEffect>(m_commonResources);
		hit->Initialize();
		m_effects.push_back(std::move(hit));
	}

	//チャージエフェクト
	auto chargeEffect = std::make_unique<ChargeEffect>(m_commonResources);
	chargeEffect->Initialize();
	m_effects.push_back(std::move(chargeEffect));


}


