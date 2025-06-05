#include "pch.h"
#include "CharacterEntity.h"
#include "Libraries/WataLib/Bounding.h"
#include "GameBase/Manager/CollisiionManager.h"
#include "Libraries/WataLib/Animation.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
CharacterEntity::CharacterEntity(CommonResources* resources
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
	:
	MoveEntity(resources, scale,position,rotation)
{

	m_animation = std::make_unique<WataLib::Animation>();

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CharacterEntity::~CharacterEntity()
{
}

/// <summary>
/// �A�j���[�V�����̓o�^
/// </summary>
/// <param name="animationType">�A�j���[�V�����̎��</param>
/// <param name="datas">�A�j���[�V�����̃f�[�^</param>
/// <param name="partsName">�p�[�c��</param>
/// <param name="isNormalAnimation">�����A�j���[�V�������ǂ���</param>
void CharacterEntity::SetAnimationData(const std::string& animationType
	, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
	, const std::string& partsName
	, bool isNormalAnimation)
{
	//�A�j���[�V�����̓o�^
	m_animation->SetAnimationData(animationType, datas[animationType][partsName], isNormalAnimation);

	//������ԂȂ�
	if (isNormalAnimation)
	{
		//���O�̕ύX
		m_currentAnimationType = animationType;
	}


}

/// <summary>
/// �A�j���[�V�����̐؂�ւ�
/// </summary>
/// <param name="animationType">�A�j���[�V�����̎��</param>
void CharacterEntity::ChangeAnimation(const std::string& animationType)
{
	//���O�̕ύX
	m_currentAnimationType = animationType;

	m_animation->ChangeAnimation(m_currentAnimationType);

}

/// <summary>
/// ������
/// </summary>
void CharacterEntity::Initialize()
{

	MoveEntity::Initialize();

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void CharacterEntity::Update(const float& elapsedTime)
{
	//�A�j���[�V�����������
	if (m_animation)
	{
		//�A�j���[�V�����̍X�V
		m_animation->Update(elapsedTime);

	}


	MoveEntity::Update(elapsedTime);


}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void CharacterEntity::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	MoveEntity::Render(view, projection);

}

/// <summary>
/// �����������ɌĂяo�����֐�
/// </summary>
/// <param name="object">����̃I�u�W�F�N�g</param>
/// <param name="tag">����̃^�O</param>
void CharacterEntity::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	MoveEntity::OnCollisionEnter(object, tag);

}
