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
/// �R���X�g���N�^
/// </summary>
EffectsManager::EffectsManager()
	:
	m_commonResources{}
	, m_effects{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EffectsManager::~EffectsManager()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
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

	//�_���[�W�G�t�F�N�g
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
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void EffectsManager::Update(const float& elapsedTime)
{

	for (auto& effect : m_effects)
	{
		effect->Update(elapsedTime);
	}

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void EffectsManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	using namespace DirectX::SimpleMath;

	for (auto& effect : m_effects)
	{

		effect->Render(view, projection);


	}

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void EffectsManager::Finalize()
{
	// do nothing.
}

/// <summary>
/// �����̐���
/// </summary>
/// <param name="datas">�f�[�^</param>
void EffectsManager::CreateExploion(void* datas)
{

	EventParams::CreateExplosionDatas* data = static_cast<EventParams::CreateExplosionDatas*>(datas);

	//�g����G�t�F�N�g�̎擾
	auto it = std::find_if(
		m_effects.begin(), m_effects.end(),
		[](const std::unique_ptr<IEffect>& effect)
		{
			return effect->GetEffectType() == IEffect::EffectType::Explosion && !effect->GetIsActive();
		});

	//�G�t�F�N�g�������
	if (it != m_effects.end())
	{
		(*it)->SetIsActive(true);
		(*it)->SetPosition(data->Position);
		(*it)->SetScale(data->Scale);
	}

}

/// <summary>
/// �_���[�W�G�t�F�N�g�̐���
/// </summary>
/// <param name="datas">�f�[�^</param>
void EffectsManager::CreatePlayerDamageEffect(void* datas)
{

	EventParams::CreateExplosionDatas* data = static_cast<EventParams::CreateExplosionDatas*>(datas);

	//�g����G�t�F�N�g�̎擾
	auto it = std::find_if(
		m_effects.begin(), m_effects.end(),
		[](const std::unique_ptr<IEffect>& effect)
		{
			return effect->GetEffectType() == IEffect::EffectType::PlayerDamage && !effect->GetIsActive();
		});

	//�G�t�F�N�g�������
	if (it != m_effects.end())
	{
		(*it)->SetIsActive(true);

	}
}

/// <summary>
/// ���G�t�F�N�g�̐���
/// </summary>
/// <param name="datas">�f�[�^</param>
void EffectsManager::CreateParticle(void* datas)
{

	EventParams::CreateExplosionDatas* data = static_cast<EventParams::CreateExplosionDatas*>(datas);

	//�g����G�t�F�N�g�̎擾
	auto it = std::find_if(
		m_effects.begin(), m_effects.end(),
		[](const std::unique_ptr<IEffect>& effect)
		{
			return effect->GetEffectType() == IEffect::EffectType::Particle && !effect->GetIsActive();
		});

	//�G�t�F�N�g�������
	if (it != m_effects.end())
	{
		
		(*it)->SetIsActive(true);
		(*it)->Create(datas);
	}


}
/// <summary>
/// �q�b�g�G�t�F�N�g�̐���
/// </summary>
/// <param name="datas">�f�[�^</param>
void EffectsManager::CreateHitEffect(void* datas)
{

	EventParams::CreateHitEffectDatas* data = static_cast<EventParams::CreateHitEffectDatas*>(datas);

	//�g����G�t�F�N�g�̎擾
	auto it = std::find_if(
		m_effects.begin(), m_effects.end(),
		[](const std::unique_ptr<IEffect>& effect)
		{
			return effect->GetEffectType() == IEffect::EffectType::HitEffect && !effect->GetIsActive();
		});

	//�G�t�F�N�g�������
	if (it != m_effects.end())
	{

		(*it)->SetIsActive(true);
		(*it)->Create(datas);
	}


}
/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�C�x���g�̎��</param>
/// <param name="datas">�C�x���g�̃f�[�^</param>
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


