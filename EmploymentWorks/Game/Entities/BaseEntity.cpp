#include "pch.h"
#include "BaseEntity.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


int BaseEntity::m_nextId = 0;

/// <summary>
/// �e�̓o�^
/// </summary>
/// <param name="parent">�e</param>
void BaseEntity::SetParent(BaseEntity* parent)
{
	m_parent = parent;

	//�e�q�֌W�������
	if (parent)
	{
		
		m_localScale = m_scale;
		m_localPosition = m_position;
		m_localRotation = m_rotation;

	}
	//�e�q�֌W����������
	else
	{

		m_worldMatrix.Decompose(m_scale, m_rotation, m_position);

	}

}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
BaseEntity::BaseEntity(CommonResources* resources
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
	:
	m_commonResources{resources}
	,m_scale{scale}
	,m_position{position}
	,m_rotation{rotation}
	, m_worldMatrix{}
	,m_localMatrix{}
	,m_localScale{}
	,m_localPosition{}
	,m_localRotation{}
	,m_parent{}
	,m_isEntityActive{true}
	,m_isUpdateActive{true}
	,m_isRenderActive{true}
{

	m_id = m_nextId;

	m_nextId++;

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BaseEntity::~BaseEntity()
{
}

/// <summary>
/// ������
/// </summary>
void BaseEntity::Initialize()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BaseEntity::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void BaseEntity::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

	//�e����
	if (m_parent)
	{

		//���[�J���s��̌v�Z
		m_localMatrix = Matrix::CreateScale(m_localScale)
			* Matrix::CreateFromQuaternion(m_localRotation)
			* Matrix::CreateTranslation(m_localPosition);

		//���[���h�s��̌v�Z�@�e������ΐe�̍s������Z
		m_worldMatrix = m_localMatrix * m_parent->GetWorldMatrix() ;

		//���[���h�s�񂩂�傫���@��]�@���W�̎擾
		m_worldMatrix.Decompose(m_scale, m_rotation, m_position);


	}
	//�e�Ȃ�
	else
	{

		//���[�J���s��̌v�Z
		m_localMatrix = Matrix::CreateScale(m_scale)
			* Matrix::CreateFromQuaternion(m_rotation)
			* Matrix::CreateTranslation(m_position);

		//���[�J���s������[���h�s���
		m_worldMatrix =  m_localMatrix;

	}


}

