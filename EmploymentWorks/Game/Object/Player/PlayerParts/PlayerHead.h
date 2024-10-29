#pragma once
#ifndef PlayerHead_DEFINED
#define PlayerHead_DEFINED
#include "Interface/IComponent.h"
#include "Game/Object/Player/PlayerParts/PlayerBase.h"


// �u�C���v�N���X���`����
class PlayerHead : public PlayerBase
{
public:
	//���݂̑傫���̎擾
	DirectX::SimpleMath::Vector3 GetScale() const { return m__currentScale; }

	//// ���݂̈ʒu���擾����
	//DirectX::SimpleMath::Vector3 GetPosition() const { return m_currentPosition; }
	//// ���݂̈ʒu��ݒ肷��
	//void SetPosition(const DirectX::SimpleMath::Vector3& currretPosition) { m_currentPosition = currretPosition; }
	// ���݂̉�]�p���擾����
	DirectX::SimpleMath::Quaternion GetAngle() const { return m_currentAngle; }
	// ���݂̉�]�p��ݒ肷��
	void SetAngle(const DirectX::SimpleMath::Quaternion& currentAngle) { m_currentAngle = currentAngle; }
	// ���f�����擾����
	DirectX::Model* GetModel() { return nullptr; }
	// ���[���h�s����擾����
	DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; }

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::EnemyParts; }

	void SetPosition(DirectX::SimpleMath::Vector3& Pos) override { m_currentPosition = Pos; }

	DirectX::SimpleMath::Vector3 GetPosition() override { return m_currentPosition; }

	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

public:
	// �R���X�g���N�^
	PlayerHead(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 scale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngleRL);
	// �f�X�g���N�^
	~PlayerHead() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(const float& elapsdTime) override;
	// �`�悷��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) override;
	// �㏈�����s��
	void Finalize() override;
	// �C�e���`���[�W����
	void ChargeBullets();
	// �C�����E�X�t�B�A���쐬����
	DirectX::BoundingSphere CreateBoundingSphere(const float& radius);
private:

	std::unique_ptr<DirectX::Model> m_model;
	//���݂̑傫��
	DirectX::SimpleMath::Vector3 m__currentScale;

	// ���݂̈ʒu
	DirectX::SimpleMath::Vector3 m_currentPosition;
	// ���݂̉�]�p
	DirectX::SimpleMath::Quaternion m_currentAngle;
	// �C�����i�z��
	std::vector<std::unique_ptr<IComponent>> m_PlayerHeadParts;
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �C�����S�_
	DirectX::SimpleMath::Vector3 m_PlayerHeadCenter;
};

#endif		// PlayerHead_DEFINED
