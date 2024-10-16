#pragma once
#ifndef ICOMPONENT_DEFINED
#define ICOMPONENT_DEFINED
#include "StepTimer.h"
#include "Interface/ICollisionObject.h"

//�G�����ɕK�v�ȕ�������̂ō��㕪����

// IComponent�C���^�[�t�F�[�X���`����
class IComponent : public ICollisionObject
{
public:
	enum AnimationStage
	{
		Success,         //����
		Runngin      //���s��

	};
public:
	// �e���擾����
	virtual IComponent* GetParent() const = 0;
	//���݂̑傫�����擾
	virtual DirectX::SimpleMath::Vector3 GetScale() const = 0;
	// ���݂̈ʒu���擾����
	//virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	// ���݂̈ʒu��ݒ肷��
	//virtual void SetPosition(const DirectX::SimpleMath::Vector3& curretPosition) = 0;
	// ���݂̉�]�p���擾����
	virtual DirectX::SimpleMath::Quaternion GetAngle() const = 0;
	// ���݂̉�]�p��ݒ肷��
	virtual void SetAngle(const DirectX::SimpleMath::Quaternion& angle) = 0;
	// ���f�����擾����
	virtual DirectX::Model* GetModel() = 0;

public:
	// ���z�f�X�g���N�^
	virtual ~IComponent() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update(const float& elapsdTime) = 0;
	// �C�����i��ǉ�����
	virtual void Attach(std::unique_ptr<IComponent> turretParts) = 0;
	// �C�����i���폜����
	virtual void Detach(std::unique_ptr<IComponent> turretPart) = 0;
	// �`�悷��
	virtual void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) = 0;
	// �㏈�����s��
	virtual void Finalize() = 0;

	virtual AnimationStage AnimationUdate(const float& elapsdTime) = 0;
	//�A�j���[�V���������s���A�j���[�V�����ɓo�^
	virtual void RegistrationRungingAnimation(std::string name) = 0;

};

#endif		// ICOMPONENT_DEFINED
