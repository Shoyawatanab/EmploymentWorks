#include "pch.h"
#include "BossEnemyPartsBase.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"

#include "Libraries/WataLib/Bounding.h"
#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Animation.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"
#include "Game/Params.h"

using namespace DirectX::SimpleMath;


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="root">�{�X�G�̍��̃N���X</param>
/// <param name="parent">�e</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="partsName">�p�[�c��</param>
/// <param name="partsHP">�p�[�c�̂g�o</param>
/// <param name="boxColliderSize">�{�b�N�X�̓����蔻��̑傫��</param>
/// <param name="SphereColliderSize">�X�t�B�A�̓����蔻��̑傫��</param>
BossEnemyPartsBase::BossEnemyPartsBase(CommonResources* resources,
	BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation, std::string partsName, int partsHP
	, DirectX::SimpleMath::Vector3 boxColliderSize, float SphereColliderSize)
	:
	CompositeEntity(resources,scale,position,rotation),
	m_model{}
	,m_root{root}
	,m_initialScale{scale}
	,m_initialPosition{position}
	,m_initialRotation{rotation}
	,m_partsName{partsName}
	,m_partsHP{partsHP}
	,m_boxColliderSize{boxColliderSize}
	,m_sphereColliderSize{SphereColliderSize}
{
	BaseEntity::SetParent(parent);
}

/// <summary>
/// ������
/// </summary>
void BossEnemyPartsBase::Initialize()
{
	CompositeEntity::Initialize();

	//�傫���̐ݒ�
	BaseEntity::SetScale(m_initialScale);
	//�e�̉�]���擾
	BaseEntity::SetRotation(m_initialRotation * CharacterEntity::GetAnimation()->GetRotation());
	//���W�̌v�Z
	BaseEntity::SetPosition(m_initialPosition + CharacterEntity::GetAnimation()->GetPosition());


	//�����蔻��̍쐬
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), m_sphereColliderSize * BaseEntity::GetScale().x);
	CollisionEntity::GetBounding()->CreateBoundingOrientedBox(BaseEntity::GetPosition(), BaseEntity::GetRotation(), m_boxColliderSize * BaseEntity::GetScale());


}



/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemyPartsBase::~BossEnemyPartsBase()
{
	
}


/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void BossEnemyPartsBase::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	//�I�u�W�F�N�g���`�悪�����Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}


	CompositeEntity::Render(view, projection);

	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();


	// ���f���̃G�t�F�N�g���X�V����
	m_model->UpdateEffects([&](DirectX::IEffect* effect)
		{
			// �x�C�V�b�N�G�t�F�N�g���擾����
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (m_partsHP > 0)
			{
				//�ʏ�F

				// �f�B�t���[�Y�J���[��ݒ肷��
				basicEffect->SetDiffuseColor(DirectX::Colors::LightSlateGray);
				// �X�y�L�����J���[��ݒ肷��
				basicEffect->SetSpecularColor(DirectX::Colors::LightSlateGray);

			}
			else
			{
				//���F

				// �f�B�t���[�Y�J���[��ݒ肷��
				basicEffect->SetDiffuseColor(DirectX::Colors::Black);
				// �X�y�L�����J���[��ݒ肷��
				basicEffect->SetSpecularColor(DirectX::Colors::Black);

			}

			// �X�y�L�����p���[��ݒ肷��
			basicEffect->SetSpecularPower(20.0f);
		});


	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection);




	CollisionEntity::GetBounding()->DrawBoundingSphere(BaseEntity::GetPosition(), view, projection);
	CollisionEntity::GetBounding()->DrawBoundingOrientedBox(BaseEntity::GetPosition(), BaseEntity::GetRotation(), view, projection);



	//�p�[�c�̕`��
	for (auto& part : CompositeEntity::GetParts())
	{
		part->Render(view, projection);
	}

}

/// <summary>
/// �����蔻��N���X�ɒǉ�
/// </summary>
/// <param name="collsionManager">�����蔻��N���X</param>
void BossEnemyPartsBase::AddCollision(CollisionManager* collsionManager)
{

	CollisionEntity::AddCollision(collsionManager);

	for (auto& part : CompositeEntity::GetParts())
	{
		part->AddCollision(collsionManager);
	}
}

/// <summary>
/// �����������ɌĂяo�����֐�
/// </summary>
/// <param name="object">����̃I�u�W�F�N�g</param>
/// <param name="tag">����̃^�O</param>
void BossEnemyPartsBase::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	switch (tag)
	{
		case CollisionEntity::CollisionTag::Boomerang:
			m_partsHP -= Params::BOOMERANG_DAMAGE;
			m_partsHP = std::max(m_partsHP, 0);
			m_root->Damage(Params::BOOMERANG_DAMAGE);

			if (m_partsHP <= 0)
			{
				//���W�����߂�
				m_root->Damage(Params::BOOMERANG_DAMAGE * 2);

				//���o���悤�ϐ�
				Vector3 position;
				Vector3 scale;
				Quaternion rotation;
				//�s�񂩂狁�߂�
				Matrix matrix = BaseEntity::GetWorldMatrix();
				matrix.Decompose(scale, rotation, position);
				EventParams::CreateExplosionDatas aa = { position ,Vector3(1,1,1) };
				Messenger::Notify(EventParams::EventType::CreateExplosion, &aa);
			}
			else
			{
				{
					EventParams::CreateHitEffectDatas aa = { object->GetPosition() ,BaseEntity::GetScale()};

					Messenger::Notify(EventParams::EventType::CreateHitEffect, &aa);
				}

			}


			break;
		case CollisionEntity::CollisionTag::Beam:
			break;
		default:
			break;
	}


}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BossEnemyPartsBase::Update(const float& elapsedTime)
{
	
	//�I�u�W�F�N�g���X�V�������Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}



	CompositeEntity::Update(elapsedTime);

	//�e�̉�]���擾
	BaseEntity::SetLocalRotation(m_initialRotation * CharacterEntity::GetAnimation()->GetRotation());
	//���W�̌v�Z
	BaseEntity::SetLocalPosition(m_initialPosition + CharacterEntity::GetAnimation()->GetPosition());


	for (auto& parts : CompositeEntity::GetParts())
	{
		parts->Update(elapsedTime);
	}


}

/// <summary>
/// �A�j���[�V�����̓o�^
/// </summary>
/// <param name="animationType">�A�j���[�V�����̎��</param>
/// <param name="datas">�A�j���[�V�����̃f�[�^</param>
/// <param name="partsName">�p�[�c��</param>
/// <param name="isNormalAnimation">�����A�j���[�V�������ǂ���</param>
void BossEnemyPartsBase::SetAnimationData(std::string animationType, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas, const std::string& partsName, bool isNormalAnimation)
{


	//�A�j���[�V�����̓o�^
	CharacterEntity::GetAnimation()->SetAnimationData(animationType, datas[animationType][m_partsName], isNormalAnimation);

	//�q�̃A�j���[�V�����̓o�^
	for (auto& part : CompositeEntity::GetParts())
	{
		part->SetAnimationData(animationType, datas, m_partsName, isNormalAnimation);
	}


}

/// <summary>
/// �A�j���[�V�����̐؂�ւ�
/// </summary>
/// <param name="animationType">�A�j���[�V�����̎��</param>
void BossEnemyPartsBase::ChangeAnimation(std::string animationType)
{

	//�A�j���[�V�����̕ύX
	CharacterEntity::GetAnimation()->ChangeAnimation(animationType);

	//�q�̃A�j���[�V�����̕ύX
	for (auto& part : CompositeEntity::GetParts())
	{
		part->ChangeAnimation(animationType);
	}

}


