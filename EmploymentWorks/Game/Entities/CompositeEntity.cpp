#include "pch.h"
#include "CompositeEntity.h"
#include "Libraries/WataLib/Bounding.h"
#include "GameBase/Manager/CollisiionManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
CompositeEntity::CompositeEntity(CommonResources* resources
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
	:
	CharacterEntity(resources, scale,position,rotation)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CompositeEntity::~CompositeEntity()
{
}

/// <summary>
/// �p�[�c�̒ǉ�
/// </summary>
/// <param name="parts">�p�[�c</param>
void CompositeEntity::AddChild(std::unique_ptr<CompositeEntity> parts)
{

	parts->Initialize();

	m_parts.push_back(std::move(parts));

}

/// <summary>
/// ������
/// </summary>
void CompositeEntity::Initialize()
{

	CharacterEntity::Initialize();

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void CompositeEntity::Update(const float& elapsedTime)
{

	CharacterEntity::Update(elapsedTime);

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void CompositeEntity::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	CharacterEntity::Render(view, projection);

}

/// <summary>
/// �����������ɌĂяo�����֐�
/// </summary>
/// <param name="object">����̃I�u�W�F�N�g</param>
/// <param name="tag">����̃^�O</param>
void CompositeEntity::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	CharacterEntity::OnCollisionEnter(object, tag);

}

/// <summary>
/// �A�j���[�V�����̓o�^
/// </summary>
/// <param name="animationType">�A�j���[�V�����̎��</param>
/// <param name="datas">�A�j���[�V�����̃f�[�^</param>
/// <param name="partsName">�p�[�c��</param>
/// <param name="isNormalAnimation">�����A�j���[�V�������ǂ���</param>
void CompositeEntity::SetAnimationData(const std::string& animationType
	, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
	, const std::string& partsName
	, bool isNormalAnimation)
{

	CharacterEntity::SetAnimationData(animationType, datas, partsName, isNormalAnimation);

}

/// <summary>
/// �A�j���[�V�����̐؂�ւ�
/// </summary>
/// <param name="animationType">�A�j���[�V�����̎��</param>
void CompositeEntity::ChangeAnimation(const std::string& animationType)
{

	CharacterEntity::ChangeAnimation(animationType);

}
