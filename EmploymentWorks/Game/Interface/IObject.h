/*
* �I�u�W�F�N�g�̃C���^�[�t�F�[�X
*/
#pragma once
#include "pch.h"

class CommonResources;


class IObject
{
public:
	//�f�X�g���N�^
	virtual ~IObject() = default;
	//������
	virtual void Initialize(CommonResources* resources) = 0;
	//���W�̎擾
	virtual const DirectX::SimpleMath::Vector3& GetPosition() = 0;
	//���W�̐ݒ�
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;
	//�傫���̎擾
	virtual const DirectX::SimpleMath::Vector3& GetScale() = 0;
	//�傫���̐ݒ�
	virtual void SetScale(const DirectX::SimpleMath::Vector3& scale) = 0;
	//��]�̎擾
	virtual const DirectX::SimpleMath::Quaternion& GetRotation() = 0;
	//��]�̐ݒ�
	virtual void SetRotation(const DirectX::SimpleMath::Quaternion& rotation) = 0;
	//�`��
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) = 0;
	//�s��̎擾
	virtual DirectX::SimpleMath::Matrix& GetMatrix() = 0;
	//�e�q�֌W�����邩�ǂ����̎擾
	virtual bool& GetIsParentActive() = 0;
	//�e�q�֌W����邩�ǂ����̐ݒ�
	virtual void SetIsParentActive(const bool& isActive) = 0;
};
