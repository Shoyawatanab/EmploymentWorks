#pragma once
#include "GameBase/Actor.h"


class Camera : public Actor
{

public:

	//���_�̎擾
	const DirectX::SimpleMath::Vector3& GetEyePosition() { return m_eye; }
	//���_�̃Z�b�g
	void SetEyePosition(const DirectX::SimpleMath::Vector3& eye) { m_eye = eye; }
	//�����_�̎擾
	const DirectX::SimpleMath::Vector3& GetTargetPosition() { return m_target; }
	//�����_�̃Z�b�g
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& target) { m_target = target; }
	//���̕����̎擾
	const DirectX::SimpleMath::Vector3& GetUpPosition() { return m_up; }
	//���̕����̃Z�b�g
	void SetUpPosition(const DirectX::SimpleMath::Vector3& up) { m_up = up; }
	//�r���[�s��̎擾
	const DirectX::SimpleMath::Matrix& GetViewMatrix() const  { return m_view; }
	//�ˉe�s��̎擾
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }
	//���ʃx�N�g���̎擾
	const DirectX::SimpleMath::Vector3& GetForwardVector() { return m_forwardVector; }
	//���ʃx�N�g���̃Z�b�g
	void SetForwardVector(const DirectX::SimpleMath::Vector3& forwardVector) { m_forwardVector = forwardVector; }

public:
	//�R���X�g���N�^
	Camera(Scene* scene);
	//�f�X�g���N�^
	~Camera() override ;

	// �X�V����
	void Update(const float& deltaTime);

	//�J�����̌ʍX�V����
	virtual void UpdateCamera(const float& deltaTime) { UNREFERENCED_PARAMETER(deltaTime); };

	// �r���[�s��̌v�Z
	void CalculateViewMatrix();

private:

	//���_
	DirectX::SimpleMath::Vector3 m_eye;
	//�����_
	DirectX::SimpleMath::Vector3 m_target;
	//���̕���
	DirectX::SimpleMath::Vector3 m_up;
	//�r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	//�ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;

	//�J�����̐��ʃx�N�g��
	DirectX::SimpleMath::Vector3 m_forwardVector;

};

