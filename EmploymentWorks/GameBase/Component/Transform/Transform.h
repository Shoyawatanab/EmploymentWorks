#pragma once
#include"GameBase/Component.h"

class Transform : public Component
{
public:
	// �������g�̈ʒu��Ԃ�
	DirectX::SimpleMath::Vector3 GetWorldPosition();
	// �������g�̑傫����Ԃ�
	DirectX::SimpleMath::Vector3 GetWorldScale();
	// �������g�̉�]��Ԃ�
	DirectX::SimpleMath::Quaternion GetWorldRotate();
	// �������g�̍s���Ԃ�
	DirectX::SimpleMath::Matrix GetWorldMatrix();

	// �ʒu�̎擾
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	//�ʒu�̃Z�b�g
	void SetPosition(const DirectX::SimpleMath::Vector3& pos);
	// �傫���̎擾
	DirectX::SimpleMath::Vector3 GetScale() const { return m_scale; }
	//�傫���̃Z�b�g
	void SetScale(const DirectX::SimpleMath::Vector3& scale);
	// ��]�̎擾
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	//��]�̃Z�b�g
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate);

	// �s��̎擾
	DirectX::SimpleMath::Matrix GetMatrix() const { return m_matrix; }


	// �ʒu�̈ړ��i���Z)
	void Translate(const DirectX::SimpleMath::Vector3& pos);
	// �傫���̕ύX(���Z)
	void TransScale(const DirectX::SimpleMath::Vector3& scale);
	// �傫���̕ύX(��Z)
	void TransScale(const float& scale);
	// ��]�̕ύX
	void TransRotate(const DirectX::SimpleMath::Quaternion& rotate);
	// ���Ɗp�x�ŉ�]����
	void TransRotate(const DirectX::SimpleMath::Vector3& axis, const float& angle);
	// ���[�J�����Ɗp�x�ŉ�]
	void LocalTransRotate(const DirectX::SimpleMath::Vector3& axis, const float& angle);
	// ���g�̎p���ɑ΂��鎲�̕�����Ԃ�
	DirectX::SimpleMath::Vector3 GetLocalAxis(const DirectX::SimpleMath::Vector3& axis);
	// ��]���l�������ʒu
	DirectX::SimpleMath::Vector3 GetRotatePosition();
	//���ʃx�N�g���̎擾
	DirectX::SimpleMath::Vector3 GetForwardVector();

	// �e���Z�b�g����
	void SetParent(Transform* parent);
	//�e���擾
	Transform* GetParent() { return m_parent; }

	// �q�̎擾
	Transform* GetChild(int num);
	// �S�Ă̎q����Ԃ�
	std::vector<Transform*> GetAllChild() { return m_children; }
	/// ���g���܂߂��q���g�����X�t�H�[����S�ĕԂ�
	std::vector<Transform*> GetAllDescendants();

public:
	// �R���X�g���N�^�A
	Transform(Actor* owner);
	//�f�X�g���N�^
	~Transform();

private:
	// �q�̃Z�b�g
	void SetChild(Transform* child) { m_children.push_back(child); }
	// �q������
	void RemoveChild(Transform* child);
	// �e�ݒ莞�̏��ύX
	void CalculationSetParent();
	// �e�������ɏ��ύX
	void CalculationRemoveParent();

	//�ċA�G�Ɏq��Ԃ��֐�
	void CollentDescendants(Transform* node, std::vector<Transform*>& tranforms);

private:
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// �傫��
	DirectX::SimpleMath::Vector3 m_scale;
	// ��]
	DirectX::SimpleMath::Quaternion m_rotate;
	// �s��
	DirectX::SimpleMath::Matrix m_matrix;
	// �s��v�Z�t���O
	bool m_isCompute;
	// �e
	Transform* m_parent;
	// �q
	std::vector<Transform*> m_children;
};