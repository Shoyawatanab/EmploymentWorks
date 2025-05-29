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
/// �R���X�g���N�^
/// </summary>
EffectsManager::EffectsManager(CommonResources* resources)
	:
	m_commonResources{resources}
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
void EffectsManager::Initialize()
{
	using namespace DirectX::SimpleMath;

	//�e�G�t�F�N�g�̍쐬
	CreateEffect();

	//���b�Z�[�W�N���X�ɓo�^
	Messenger::GetInstance()->Rigister(GamePlayMessageType::PLAYER_DAMAGE, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::CREATE_EXPLOSION, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::CREATE_PARTICLE, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::CREATE_HIT_EFFECT, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::CREATE_CHAGE_EFFECT, this);

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void EffectsManager::Update(const float& elapsedTime)
{
	//�G�t�F�N�g�̍X�V
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

	//�G�t�F�N�g�̕`��
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
	//�f�[�^�̎擾
	UnknownDataTwo* data = static_cast<UnknownDataTwo*>(datas);

	//�g����G�t�F�N�g�̎擾
	auto it = std::find_if(
		m_effects.begin(), m_effects.end(),
		[](const std::unique_ptr<IEffect>& effect)
		{
			return effect->GetEffectType() == IEffect::EffectType::EXPLOSION && !effect->GetIsActive();
		});

	//�G�t�F�N�g�������
	if (it != m_effects.end())
	{
		(*it)->SetIsActive(true);
		(*it)->SetPosition(*static_cast<DirectX::SimpleMath::Vector3*>(data->data1));
		(*it)->SetScale(*static_cast<DirectX::SimpleMath::Vector3*>(data->data2));
	}

}

/// <summary>
/// �_���[�W�G�t�F�N�g�̐���
/// </summary>
/// <param name="datas">�f�[�^</param>
void EffectsManager::CreatePlayerDamageEffect(void* datas)
{
	UNREFERENCED_PARAMETER(datas);

	//�g����G�t�F�N�g�̎擾
	auto it = std::find_if(
		m_effects.begin(), m_effects.end(),
		[](const std::unique_ptr<IEffect>& effect)
		{
			return effect->GetEffectType() == IEffect::EffectType::PLAYER_DAMAGE && !effect->GetIsActive();
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
	UNREFERENCED_PARAMETER(datas);

	//CreateExplosionDatas* data = static_cast<CreateExplosionDatas*>(datas);

	//�g����G�t�F�N�g�̎擾
	auto it = std::find_if(
		m_effects.begin(), m_effects.end(),
		[](const std::unique_ptr<IEffect>& effect)
		{
			return effect->GetEffectType() == IEffect::EffectType::PARTICLE && !effect->GetIsActive();
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
	UNREFERENCED_PARAMETER(datas);

	//CreateHitEffectDatas* data = static_cast<CreateHitEffectDatas*>(datas);

	//�g����G�t�F�N�g�̎擾
	auto it = std::find_if(
		m_effects.begin(), m_effects.end(),
		[](const std::unique_ptr<IEffect>& effect)
		{
			return effect->GetEffectType() == IEffect::EffectType::HIT_EFFECT && !effect->GetIsActive();
		});

	//�G�t�F�N�g�������
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

	//�g����G�t�F�N�g�̎擾
	auto it = std::find_if(
		m_effects.begin(), m_effects.end(),
		[](const std::unique_ptr<IEffect>& effect)
		{
			return effect->GetEffectType() == IEffect::EffectType::CHARGE_EFFECT && !effect->GetIsActive();
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
void EffectsManager::Notify(const Telegram<GamePlayMessageType>& telegram)
{

	switch (telegram.messageType)
	{
		//�����̐���
		case GamePlayMessageType::CREATE_EXPLOSION:
			CreateExploion(telegram.extraInfo);
			break;
		//�v���C���̃_���[�W�G�t�F�N�g�̐���
		case GamePlayMessageType::PLAYER_DAMAGE:
			CreatePlayerDamageEffect(telegram.extraInfo);
			break;
		//�p�[�e�B�N���G�t�F�N�g�̐���
		case GamePlayMessageType::CREATE_PARTICLE:
			CreateParticle(telegram.extraInfo);
			break;
		//�q�b�g�G�t�F�N�g�̐���
		case GamePlayMessageType::CREATE_HIT_EFFECT:
			//CreateHitEffect(datas);
			break;
		//�`���[�W�G�t�F�N�g�̐���
		case GamePlayMessageType::CREATE_CHAGE_EFFECT:
			CreateChargeEffect(telegram.extraInfo);
			break;
		default:
			break;
	}

}

/// <summary>
/// �G�t�F�N�g�̍쐬
/// </summary>
void EffectsManager::CreateEffect()
{

	//�����G�t�F�N�g
	for (int i = 0; i < EXPLOION_EFFECT_COUNT; i++)
	{
		auto explosion = std::make_unique<ExplosionEffects>(m_commonResources);
		explosion->Initialize();

		m_effects.push_back(std::move(explosion));
	}

	//�_���[�W�G�t�F�N�g
	auto damegeVignette = std::make_unique<DamageVignette>(m_commonResources);
	damegeVignette->Initialize();
	m_effects.push_back(std::move(damegeVignette));

	//�p�[�e�B�N���G�t�F�N�g
	for (int i = 0; i < PARTICLE_EFFECT_COUNT;i++)
	{
		auto particle = std::make_unique < Particle>(m_commonResources);
		particle->Initialize();

		m_effects.push_back(std::move(particle));

		particle = std::make_unique < Particle>(m_commonResources);
		particle->Initialize();

		m_effects.push_back(std::move(particle));

	}


	//�q�b�g�G�t�F�N�g
	for (int i = 0; i < HIT_EFFECT_COUNT; i++)
	{
		auto hit = std::make_unique<HitEffect>(m_commonResources);
		hit->Initialize();
		m_effects.push_back(std::move(hit));
	}

	//�`���[�W�G�t�F�N�g
	auto chargeEffect = std::make_unique<ChargeEffect>(m_commonResources);
	chargeEffect->Initialize();
	m_effects.push_back(std::move(chargeEffect));


}


