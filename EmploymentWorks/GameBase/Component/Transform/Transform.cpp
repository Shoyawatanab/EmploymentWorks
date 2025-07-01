#include"pch.h"
#include"Transform.h"

Transform::Transform(Actor* owner)
	:
	Component{owner}
	,m_position{DirectX::SimpleMath::Vector3::Zero}
	,m_scale{DirectX::SimpleMath::Vector3::One}
	,m_rotate{DirectX::SimpleMath::Quaternion::Identity}
	,m_isCompute{false}
	,m_parent{nullptr}
	,m_children{}
{

}

Transform::~Transform()
{

}


/// <summary>
/// ���[���h�s��擾
/// </summary>
DirectX::SimpleMath::Matrix Transform::GetWorldMatrix()
{
	using namespace DirectX::SimpleMath;

	// �v�Z�t���O�������Ă���ꍇ�v�Z����
	if (m_isCompute)
	{
		// �傫������]���ʒu�̌v�Z��
		m_matrix = Matrix::CreateScale(m_scale);
		m_matrix *= Matrix::CreateFromQuaternion(m_rotate);
		m_matrix *= Matrix::CreateTranslation(m_position);
		m_isCompute = false;
	}

	Matrix worldMatrix = m_matrix;

	// �e������ꍇ�ɁA�e�̍s���������
	if (m_parent != nullptr)
	{
		worldMatrix *= m_parent->GetWorldMatrix();
	}
	// �s���Ԃ�
	return worldMatrix;
}

/// <summary>
/// ���[���h�̈ʒu��Ԃ�
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::GetWorldPosition()
{
	using namespace DirectX::SimpleMath;

	Vector3 worldPos = m_position;
	// �e������ꍇ�A�e�̃|�W�V�����𑫂�
	if (m_parent != nullptr)
	{
		worldPos += m_parent->GetWorldPosition();
	}
	// �ʒu��Ԃ�
	return worldPos;
}

/// <summary>
/// ���[���h�̃X�P�[����Ԃ�
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::GetWorldScale()
{
	using namespace DirectX::SimpleMath;

	Vector3 worldScale = m_scale;
	// �e������ꍇ�A�e�̑傫���𑫂�
	if (m_parent != nullptr)
	{
		worldScale += m_parent->GetWorldScale();
	}
	return worldScale;
}

/// <summary>
/// ���[���h��]��Ԃ�
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Quaternion Transform::GetWorldRotate()
{
	using namespace DirectX::SimpleMath;

	Quaternion worldRotate = m_rotate;
	// �e������ꍇ�A�e�̉�]��������
	if (m_parent != nullptr)
	{
		worldRotate *= m_parent->GetWorldRotate();
	}
	return worldRotate;
}

/// <summary>
/// �|�W�V�������Z�b�g����
/// </summary>
/// <param name="position"></param>
void Transform::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
	m_isCompute = true;
}

/// <summary>
/// �X�P�[�����Z�b�g����
/// </summary>
/// <param name="scale"></param>
void Transform::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale = scale;
	m_isCompute = true;
}

/// <summary>
/// ��]���Z�b�g����
/// </summary>
/// <param name="rotate"></param>
void Transform::SetRotate(const DirectX::SimpleMath::Quaternion& rotate)
{
	m_rotate = rotate;
	m_isCompute = true;
}

/// <summary>
/// �ʒu�ړ��i���Z�j
/// </summary>
/// <param name="position"></param>
void Transform::Translate(const DirectX::SimpleMath::Vector3& position)
{
	m_position += position;
	m_isCompute = true;
}

/// <summary>
/// �X�P�[���ω�(���Z)
/// </summary>
/// <param name="scale"></param>
void Transform::TransScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale += scale;
	m_isCompute = true;
}

/// <summary>
/// �X�P�[���ω�(��Z)
/// </summary>
/// <param name="scale"></param>
void Transform::TransScale(const float& scale)
{
	m_scale *= scale;
	m_isCompute = true;
}

/// <summary>
/// ��](�N�H�[�^�j�I��)
/// </summary>
/// <param name="rotate"></param>
void Transform::TransRotate(const DirectX::SimpleMath::Quaternion& rotate)
{
	m_rotate = m_rotate * rotate;
	m_isCompute = true;
}

/// <summary>
/// ��](�� , �p�x)
/// </summary>
void Transform::TransRotate(const DirectX::SimpleMath::Vector3& axis, const float& angle)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	Quaternion quaternion = Quaternion::CreateFromAxisAngle(axis, XMConvertToRadians(angle));
	TransRotate(quaternion);
}

/// <summary>
/// ���[�J����]
/// </summary>
void Transform::LocalTransRotate(const DirectX::SimpleMath::Vector3& axis, const float& angle)
{
	using namespace DirectX::SimpleMath;

	Vector3 localAxis = GetLocalAxis(axis);
	TransRotate(localAxis, angle);
}


/// <summary>
/// ���̕�����Ԃ�
/// </summary>
DirectX::SimpleMath::Vector3 Transform::GetLocalAxis(const DirectX::SimpleMath::Vector3& axis)
{
	using namespace DirectX::SimpleMath;

	Vector3 localAxis = Vector3::Transform(axis, m_rotate);
	localAxis.Normalize();
	return localAxis;
}

/// <summary>
/// �e�̉�]���l�������|�W�V������Ԃ�
/// </summary>
DirectX::SimpleMath::Vector3 Transform::GetRotatePosition()
{
	using namespace DirectX::SimpleMath;

	if (m_parent == nullptr) 
	{ 
		return m_position; 
	}

	Vector3 distance = m_position * m_parent->m_scale;
	distance = Vector3::Transform(distance, m_parent->GetWorldRotate());
	return m_parent->GetRotatePosition() + distance;
}



/// <summary>
/// ���ʃx�N�g���̎擾
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::GetForwardVector()
{
	using namespace DirectX::SimpleMath;

	Vector3 forward = Vector3::Transform(Vector3::Backward, m_rotate);
	forward.Normalize();

	return forward;
}

/// <summary>
/// �e�̃Z�b�g
/// </summary>
/// <param name="parent"></param>
void Transform::SetParent(Transform* parent)
{
	// �e�����Ȃ��ꍇ
	if (parent == nullptr)
	{
		// ������null�ŁA���łɐe������ꍇ
		if (m_parent != nullptr)
		{
			// �e�̏�񂩂�t�Z�������ɂ���
			CalculationRemoveParent();
			// �e�������
			m_parent->RemoveChild(this);
			m_parent = nullptr;
		}
	}
	else
	{
		// ����������A���݂̐e�ƈႤ�ꍇ
		if (m_parent != parent)
		{
			if (m_parent != nullptr)
			{
				// ���̐e�̏�񂩂�t�Z�������ɂ���
				CalculationRemoveParent();
			}
			// �e�̐ݒ�
			m_parent = parent;
			m_parent->SetChild(this);
			CalculationSetParent();
		}
	}
}

/// <summary>
/// �q���擾����
/// </summary>
/// <param name="num">�C���f�b�N�X�ԍ�</param>
/// <returns></returns>
Transform* Transform::GetChild(int num)
{
	// ���͂��ꂽ�C���f�b�N�X�ԍ����T�C�Y��葽���ꍇ�Anullptr��Ԃ�
	if (num >= m_children.size()) 
	{ 
		return nullptr; 
	}
	// �q��Ԃ�
	return m_children[num];
}

/// <summary>
/// ���g���܂߂��q���g�����X�t�H�[����S�ĕԂ�
/// </summary>
/// <returns>�q���g�����X�t�H�[��</returns>
std::vector<Transform*> Transform::GetAllDescendants()
{
	//�i�[�ϐ�
	std::vector<Transform*> transforms;
	//���g���ǉ�
	transforms.push_back(this);
	//�q���m�[�h��T��
	CollentDescendants(this, transforms);

	return transforms;
}

/// <summary>
/// �q���폜����
/// </summary>
/// <param name="child"></param>
void Transform::RemoveChild(Transform* child)
{
	// �q��T��
	auto searchChiled = std::find(m_children.begin(), m_children.end(), child);

	if (searchChiled != m_children.end())
	{
		// �q�������̂Ȃ�����A����̎q���폜
		m_children.erase(searchChiled);
	}
}

/// <summary>
/// �e��ݒ肵���ۂɁA����ύX����
/// </summary>
void Transform::CalculationSetParent()
{
	using namespace DirectX::SimpleMath;

	// �ʒu�̈ړ�
	m_position -= m_parent->m_position;
	// �X�P�[���̕ϊ�
	m_scale = Vector3
	{
		m_scale.x / m_parent->m_scale.x,
		m_scale.y / m_parent->m_scale.y,
		m_scale.z / m_parent->m_scale.z,
	};
	// ��]�̕ϊ�
	Quaternion invers = m_parent->m_rotate;
	invers.Inverse(invers);
	m_rotate *= invers;
	// ��]�ړ�
	DirectX::SimpleMath::Vector3 dire = m_position;
	dire = Vector3(
		dire.x / m_parent->m_scale.x,
		dire.y / m_parent->m_scale.y,
		dire.z / m_parent->m_scale.z
	);
	// �s��̕ϊ�
	Matrix mat = Matrix::CreateFromQuaternion(invers);
	m_position = Vector3::Transform(dire, mat);
	// �v�Z�I��
	m_isCompute = true;
}

/// <summary>
/// �e�����������ۂ̏��ύX
/// </summary>
void Transform::CalculationRemoveParent()
{
	using namespace DirectX::SimpleMath;

	// ��]�擾
	Quaternion invers = m_parent->GetWorldRotate();
	// �ʒu�擾
	Vector3 dire = m_position;
	dire = Vector3(
		dire.x * m_parent->m_scale.x,
		dire.y * m_parent->m_scale.y,
		dire.z * m_parent->m_scale.z
	);
	// �s��̎擾
	Matrix mat = Matrix::CreateFromQuaternion(invers);
	// �ʒu��ύX
	m_position = Vector3::Transform(dire, mat);

	m_position += m_parent->m_position;
	m_scale = Vector3(
		m_scale.x * m_parent->m_scale.x,
		m_scale.y * m_parent->m_scale.y,
		m_scale.z * m_parent->m_scale.z
	);

	m_rotate *= m_parent->m_rotate;
	m_isCompute = true;
}

/// <summary>
/// �ċA�I�Ɏq����Ԃ�
/// </summary>
/// <param name="node">�ǂ̃g�����X�t�H�[����</param>
/// <param name="tranforms">�i�[�ϐ�</param>
void Transform::CollentDescendants(Transform* node, std::vector<Transform*>& tranforms)
{
	//�q�m�[�h��
	for (auto& child : node->GetAllChild())
	{
		//�g�����X�t�H�[���Ɋi�[
		tranforms.push_back(child);
		//�q�̎q��T���ĕԂ�
		CollentDescendants(child, tranforms);
	}

}
