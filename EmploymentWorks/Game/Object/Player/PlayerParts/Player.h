#pragma once
#ifndef Player_DEFINED
#define Player_DEFINED
#include "Interface/IComponent.h"
#include  "Game/Player/PlayerBase.h"



// �u�C���v�N���X���`����
class Player : public PlayerBase
{
public:
	//���݂̑傫���̎擾
	DirectX::SimpleMath::Vector3 GetScale() const override { return m__currentScale; }
	// ���݂̈ʒu���擾����
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_currentPosition; }
	// ���݂̈ʒu��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector3& currretPosition) { m_currentPosition = currretPosition; }
	// ���݂̉�]�p���擾����
	DirectX::SimpleMath::Quaternion GetAngle() const { return m_currentAngle; }
	// ���݂̉�]�p��ݒ肷��
	void SetAngle(const DirectX::SimpleMath::Quaternion& currentAngle) { m_currentAngle = currentAngle; }
	// ���f�����擾����
	DirectX::Model* GetModel() { return nullptr; }
	// ���[���h�s����擾����
	DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; }

public:
	// �R���X�g���N�^
	Player(CommonResources* resources,IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngleRL);
	// �f�X�g���N�^
	~Player() override;
	// ����������
	void Initialize() override;
	// �L�[�{�[�h�C�x���g����������
	inline void HandleKeyboardEvent();
	// �X�V����
	void Update(const float& elapsdTime) override;
	// �`�悷��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) override;
	// �㏈�����s��
	void Finalize() override;
	// �C�����E�X�t�B�A���쐬����
	DirectX::BoundingSphere CreateBoundingSphere(const float& radius);
private:
	//���݂̑傫��
	DirectX::SimpleMath::Vector3 m__currentScale;
	// ���݂̈ʒu
	DirectX::SimpleMath::Vector3 m_currentPosition;
	// ���݂̉�]�p
	DirectX::SimpleMath::Quaternion m_currentAngle;
	// �C�����i�z��
	std::vector<std::unique_ptr<IComponent>> m_PlayerParts;
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �C�����S�_
	DirectX::SimpleMath::Vector3 m_PlayerCenter;



};

#endif		// Player_DEFINED


//Player�S�̂̏�������