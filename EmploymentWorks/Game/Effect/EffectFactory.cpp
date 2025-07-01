#include"pch.h"
#include "EffectFactory.h"
#include "Effects.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
EffectFactory::EffectFactory(Scene* scene)
	:
	Actor(scene)
	,m_explosiions{}
{

	//�����G�t�F�N�g�̍쐬
	for(int i = 0; i < 10; i++)
	{

		auto explosition = GetScene()->AddActor<Explosiion>(GetScene());
		m_explosiions.push_back(explosition);

	}



	for (int i = 0; i < 10; i++)
	{

		auto charge = GetScene()->AddActor<BossChargeEffect>(GetScene());

		m_chargeEffects.push_back(charge);
	}

	for (int i = 0; i < 10; i++)
	{
		auto particle = GetScene()->AddActor<Particle>(GetScene());

		m_particles.push_back(particle);

	}


	SceneMessenger::GetInstance()->Rigister({
		SceneMessageType::EXPLOSITION_EFFECT
		,SceneMessageType::CREATE_CHARGE_EFFECT
		,SceneMessageType::CREATE_PARTICLE_EFFECT
		}, this
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EffectFactory::~EffectFactory()
{
}

/// <summary>
/// �ʒm���ɌĂ΂��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void EffectFactory::Notify(SceneMessageType type, void* datas)
{

	switch (type)
	{

		case SceneMessageType::EXPLOSITION_EFFECT:
		{
			ExplosionEffectDatas data = *static_cast<ExplosionEffectDatas*>(datas);

			for (auto& explosiion : m_explosiions)
			{
				//��A�N�e�B�u��Ԃ�T��
				if (!explosiion->GetActive())
				{
					//�A�N�e�B�u��Ԃ�
					explosiion->SetActive(true);
					//�ǉ��f�[�^����f�[�^�̃Z�b�g
					explosiion->GetTransform()->SetScale(data.Scale);
					explosiion->GetTransform()->SetPosition(data.Position);

					break;

				}
			}

		}
			break;
		case SceneMessageType::CREATE_CHARGE_EFFECT:
		{
			CreateChargeEffectDatas data = *static_cast<CreateChargeEffectDatas*>(datas);

			for (auto& charge : m_chargeEffects)
			{
				if (!charge->GetActive())
				{

					charge->SetActive(true);
					charge->GetTransform()->SetPosition(data.Position);
					charge->GetTransform()->SetScale(data.Scale);

					break;
				}
			}

		}
			break;
		case SceneMessageType::CREATE_PARTICLE_EFFECT:
		{

			for (auto& particle : m_particles)
			{
				if (!particle->GetActive())
				{

					DirectX::SimpleMath::Vector3 position = *static_cast<DirectX::SimpleMath::Vector3*>(datas);


					particle->GetTransform()->SetPosition(position);

					particle->SetActive(true);


					break;
				}
			}

		}
			
			break;
		default:
			break;
	}

}
