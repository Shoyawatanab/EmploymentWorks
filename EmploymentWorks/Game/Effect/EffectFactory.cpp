/*
	�N���X��     : EffectFactory
	����         : �G�t�F�N�g�̍쐬�E�Ǘ����s���N���X
	�⑫�E���ӓ_ :
*/
#include"pch.h"
#include "EffectFactory.h"
#include "Effects.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"

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

	//�ʒm���󂯎��R���|�[�l���g�̒ǉ�
	auto ob = AddComponent<ObserverComponent<SceneMessageType>>(this);
	//�ǂ̒ʒm���̓o�^�ƌĂяo���֐��̓o�^
	ob->Rigister(
		{
			SceneMessageType::EXPLOSITION_EFFECT
			,SceneMessageType::CREATE_CHARGE_EFFECT
			,SceneMessageType::CREATE_PARTICLE_EFFECT
		}
		, std::bind(&EffectFactory::Notify, this, std::placeholders::_1, std::placeholders::_2)
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
