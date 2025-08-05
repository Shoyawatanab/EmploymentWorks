/*
	�N���X��     : BossEnemy
	����         : �{�X�G�̃p�[�c�̊��N���X
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "BossEnemyParts.h"
#include "Game/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Params.h"
#include "Game/Messenger/Messengers.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Camera/Camera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
/// <param name="partsName">�p�[�c��</param>
/// <param name="modelName">���f����</param>
/// <param name="hp">�p�[�cHP</param>
/// <param name="boss">��{�̃N���X</param>
BossEnemyParts::BossEnemyParts(Scene* scene, std::string partsName,std::string modelName
	,int hp, DirectX::SimpleMath::Vector3 boxColliderExtens, float sphereRadius
	, BossEnemy* boss)
	:
	ModelPartsBase(scene,partsName,modelName)
	,m_hp{hp}
	,m_bossEnemy{boss}
{
	//�������\�[�X�̎擾
	m_commonResources = CommonResources::GetInstance();
	//�����蔻��̒ǉ�
	auto obb = AddComponent<OBB>(this,  CollisionType::TRIGGER
		, boxColliderExtens
		, DirectX::SimpleMath::Quaternion::Identity
		, sphereRadius);
	//�����蔻����s��Ȃ��^�O�̒ǉ�
	obb->SetNotHitObjectTag({
		Actor::ObjectTag::BOSS_ENEMY
		});
	//�d�͂̒ǉ�
	auto rigigdBody = AddComponent<RigidbodyComponent>(this);
	rigigdBody->SetActive(false);


	//�J�X�^���`��̒ǉ�
	GetModelComponent()->SetCustomRenderFunction(std::bind(&BossEnemyParts::Render, this, std::placeholders::_1));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemyParts::~BossEnemyParts()
{
}

/// <summary>
/// �����������̊֐�
/// </summary>
/// <param name="collider">����̃R���C�_�[</param>
void BossEnemyParts::OnCollisionEnter(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case ObjectTag::BOOMERANG:
		{
			//�p�[�c��Hp����
			HpDecrease(Params::BOOMERANG_DAMAGE);

			//�\���̂̍쐬
			EnemyDamageDatas datas;
			//�f�[�^�̃Z�b�g
			datas.Damage = Params::BOOMERANG_DAMAGE;
			datas.Position = GetTransform()->GetWorldPosition();

			Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::ENEMY_DAMAGE, &datas);

			//�{�X�G�Ƀ_���[�W�̉��Z
			m_bossEnemy->AddDamage(Params::BOOMERANG_DAMAGE);


		}
			break;
		default:
			break;
	}

	//�p�[�c���Ƃ̔���
	OnCollisionEnterActor(collider);

}

/// <summary>
/// HP����
/// </summary>
/// <param name="damage">�_���[�W</param>
void BossEnemyParts::HpDecrease(int damage)
{
	//���łɔj�󂳂�Ă���Ȃ珈�����Ȃ�����
	if (m_hp == 0)
	{
		return;
	}
	//HP�̌���
	m_hp -= damage;
	//0�ȉ��ɂȂ�Ȃ��悤��
	m_hp = std::max(m_hp, 0);

	if (m_hp == 0)
	{
		//�p�[�c���Ƃ̔j�󏈗�
		PartsDestruction();
		//�{�X�G�ɕ��ʔj��_���[�W�̉��Z
		m_bossEnemy->AddDamage(Params::BOOMERANG_DAMAGE * 5);

		//�����G�t�F�N�g�̒ʒm
		ExplosionEffectDatas datas;
		//�ǉ��f�[�^����f�[�^�̃Z�b�g
		datas.Position = GetTransform()->GetWorldPosition();
		datas.Scale = GetTransform()->GetWorldScale();
		Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::EXPLOSITION_EFFECT, &datas);


	}

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="camera">�J����</param>
void BossEnemyParts::Render(const Camera& camera)
{
	auto model = GetModelComponent()->GetModel();

	if (m_hp <= 0)
	{
		// ���f���̃G�t�F�N�g���X�V����
		model->UpdateEffects([&](DirectX::IEffect* effect)
			{
				// �x�C�V�b�N�G�t�F�N�g���擾����
				auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
				// �f�B�t���[�Y�J���[��ݒ肷��
				basicEffect->SetDiffuseColor(DirectX::Colors::Black);
				// �X�y�L�����J���[��ݒ肷��
				basicEffect->SetSpecularColor(DirectX::Colors::Black);
				// �X�y�L�����p���[��ݒ肷��
				basicEffect->SetSpecularPower(20.0f);
			});

	}
	else
	{
		// ���f���̃G�t�F�N�g���X�V����
		model->UpdateEffects([&](DirectX::IEffect* effect)
			{
				// �x�C�V�b�N�G�t�F�N�g���擾����
				auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
				// �f�B�t���[�Y�J���[��ݒ肷��
				basicEffect->SetDiffuseColor(DirectX::Colors::LightSlateGray);
				// �X�y�L�����J���[��ݒ肷��
				basicEffect->SetSpecularColor(DirectX::Colors::LightSlateGray);
				// �X�y�L�����p���[��ݒ肷��
				basicEffect->SetSpecularPower(20.0f);
			});

	}

	//���f���`��
	model->Draw(m_commonResources->GetDeviceResources()->GetD3DDeviceContext()
		, *m_commonResources->GetCommonStates()
		, GetTransform()->GetWorldMatrix()
		, camera.GetViewMatrix()
		, camera.GetProjectionMatrix());
}
