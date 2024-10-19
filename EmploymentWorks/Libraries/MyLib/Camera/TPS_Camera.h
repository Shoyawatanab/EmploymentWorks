/*
	@file	TPS_Camera.h
	@brief	TPS�J�����N���X
*/
#pragma once
#include "Interface/IGameCamera.h"

class Player;

namespace mylib
{
	class Mouse;
}

namespace mylib
{
	class TPS_Camera :public IGameCamera
	{
	private:
		struct MouseSensitivity //�}�E�X���x�̍\����
		{
			float x;
			float y;
		};

		enum class ZoomState
		{
			None,
			ZoomIn,
			ZoomOut
		};



	public:
		// getter
		const DirectX::SimpleMath::Matrix& GetViewMatrix() override  { return m_view; }

		const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }

		const DirectX::SimpleMath::Vector3& GetEyePosition() const { return m_eye; }

		void SetEyePosition(DirectX::SimpleMath::Vector3 pos) {
			m_eye = pos; 	// �J�������W���v�Z����
			// �r���[�s����X�V����
			CalculateViewMatrix();
		}

		const DirectX::SimpleMath::Vector3& GetTargetPosition() const { return m_target; }

		const DirectX::SimpleMath::Vector3& GetUpVector() const { return m_up; }

		DirectX::SimpleMath::Quaternion GetRotationX() { return m_rotationX; }

		DirectX::SimpleMath::Vector3 GetCameraForward() { return m_forward; }

		//�f�o�b�N�p
		const POINT GetAngle() { return m_angle; }

	private:
		// �^�[�Q�b�g����̃f�t�H���g����
		const float CAMERA_DISTANCE = 4.0f;
		const float CAMERA_HIGHT = 0.0f;

		// ��p
		const float FOV = DirectX::XMConvertToRadians(45.0f);
		
		// �߂����e��
		const float NEAR_PLANE = 1.0f;
		
		// �������e��
		const float FAR_PLANE  = 100.0f;

		// �r���[�s��
		DirectX::SimpleMath::Matrix m_view;

		// �v���W�F�N�V�����s��
		DirectX::SimpleMath::Matrix m_projection;

		// �J�������W
		DirectX::SimpleMath::Vector3 m_eye;

		// �����_
		DirectX::SimpleMath::Vector3 m_target;

		// �J�����̓��̕���
		DirectX::SimpleMath::Vector3 m_up;

		Player* m_player;

		DirectX::SimpleMath::Quaternion m_rotationX;

		mylib::Mouse* m_mouse;
		//��]�p�x
		POINT m_angle;
		//�}�E�X���x
		MouseSensitivity m_mouseSensitivity;

		float m_lerpTime;

		//�\�������̃J�����̓�������
		DirectX::SimpleMath::Vector3 m_moveEye;

		ZoomState m_zoomState;

		DirectX::SimpleMath::Vector3 m_forward;


	public:
		// �R���X�g���N�^
		TPS_Camera();

		// �f�X�g���N�^
		~TPS_Camera();

		//�N���X�ɕK�v�ȏ��i�|�C���^�j��o�^����
		void RegistrationInformation(Player* Player);


		//�I�[�o�[���C�h
	public:
		// ����������
		void Initialize() override ;


		// �X�V����
		void Update(const float& elapsedTime) override;

		void Enter() override;

		void Exit() override;


	private:
		// �r���[�s����v�Z����
		void CalculateViewMatrix();

		// �v���W�F�N�V�����s����v�Z����
		void CalculateProjectionMatrix();

		// �J�������W���v�Z����
		void CalculateEyePosition();


	};
}
