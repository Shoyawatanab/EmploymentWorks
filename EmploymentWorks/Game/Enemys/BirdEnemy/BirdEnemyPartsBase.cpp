#include "pch.h"
#include "BirdEnemyPartsBase.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"

#include "Libraries/WataLib/Bounding.h"
#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Animation.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// ������
/// </summary>
void BirdEnemyPartsBase::Initialize()
{
	CompositeEntity::Initialize();
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="parent">�e</param>
/// <param name="partsName">�p�[�c��</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
BirdEnemyPartsBase::BirdEnemyPartsBase(CommonResources* resources, CharacterEntity* parent, std::string partsName, DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation)
	:
	CompositeEntity(resources, scale, position, rotation)
	,m_model{}
	,m_partsName{ partsName }
	, m_initialScale{ scale }
	, m_initialPosition{ position }
	, m_initialRotation{ rotation }
	
{
	BaseEntity::SetParent(parent);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyPartsBase::~BirdEnemyPartsBase()
{
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void BirdEnemyPartsBase::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	//�I�u�W�F�N�g���`�悪�����Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}


	CompositeEntity::Render(view, projection);

	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();

	


	//���f���̕`��
	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection);

	//�p�[�c�̕`��
	for (auto& part : CompositeEntity::GetParts())
	{
		part->Render(view,projection);
	}

}

/// <summary>
/// �����������ɌĂяo�����֐�
/// </summary>
/// <param name="object">����I�u�W�F�N�g</param>
/// <param name="tag">����̃^�O</param>
void BirdEnemyPartsBase::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{
	UNREFERENCED_PARAMETER(object);
	UNREFERENCED_PARAMETER(tag);

}


/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BirdEnemyPartsBase::Update(const float& elapsedTime)
{
	//�I�u�W�F�N�g���X�V�������Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}

	//CompositeEntity::Update(elapsedTime);

	////�e�̉�]���擾
	//BaseEntity::SetLocalRotation(m_initialRotation * CharacterEntity::GetAnimation()->GetRotation());
	////���W�̌v�Z
	//BaseEntity::SetLocalPosition(m_initialPosition + CharacterEntity::GetAnimation()->GetPosition());

	//�p�[�c�̕`��
	for (auto& part : CompositeEntity::GetParts())
	{
		part->Update(elapsedTime);
	}
}


/// <summary>
/// �A�j���[�V�����̓o�^
/// </summary>
/// <param name="animationType">�A�j���[�V�����̎��</param>
/// <param name="datas">�A�j���[�V�����f�[�^</param>
/// <param name="partsName">�p�[�c��</param>
/// <param name="isNormalAnimation">�����A�j���[�V�������ǂ���</param>
void BirdEnemyPartsBase::SetAnimationData(std::string animationType, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas, const std::string& partsName, bool isNormalAnimation)
{
		UNREFERENCED_PARAMETER(partsName);

	//�A�j���[�V�����̓o�^
	CharacterEntity::GetAnimation()->SetAnimationData(animationType, datas[animationType][m_partsName], isNormalAnimation);

	//�q�̃A�j���[�V�����̓o�^
	for (auto& part : CompositeEntity::GetParts())
	{
		part->SetAnimationData(animationType, datas, m_partsName, isNormalAnimation);
	}

}

/// <summary>
/// �A�j���[�V�����̕ύX
/// </summary>
/// <param name="animationType">�A�j���[�V�����̎��</param>
void BirdEnemyPartsBase::ChangeAnimation(std::string animationType)
{

	//�A�j���[�V�����̕ύX
	CharacterEntity::GetAnimation()->ChangeAnimation(animationType);

	//�q�̃A�j���[�V�����̕ύX
	for (auto& part : CompositeEntity::GetParts())
	{
		part->ChangeAnimation(animationType);
	}
}

