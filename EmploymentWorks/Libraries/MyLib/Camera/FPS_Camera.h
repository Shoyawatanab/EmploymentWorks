/*
	@file	FPS_Camera.h
	@brief	FPS�J�����N���X
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
	class FPS_Camera :public IGameCamera
	{
	public:
		const DirectX::SimpleMath::Matrix& GetViewMatrix() override { return m_view; }


		const DirectX::SimpleMath::Vector2& Angle() { return m_angle; }
	private:


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
		mylib::Mouse* m_mouse;
		//��]�p�x
		DirectX::SimpleMath::Vector2 m_angle;


	public:
		// �R���X�g���N�^
		FPS_Camera(
			const DirectX::SimpleMath::Vector3& eye = DirectX::SimpleMath::Vector3{ 0.0f,2.0f,10.0f },
			const DirectX::SimpleMath::Vector3& target = DirectX::SimpleMath::Vector3::Zero,
			const DirectX::SimpleMath::Vector3& up = DirectX::SimpleMath::Vector3::UnitY
		);

		// �f�X�g���N�^
		~FPS_Camera();

		//�N���X�ɕK�v�ȏ��i�|�C���^�j��o�^����
		void RegistrationInformation(Player* Player);


		// getter
		const DirectX::SimpleMath::Matrix& GetViewMatrix() const { return m_view; }

		const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }

		const DirectX::SimpleMath::Vector3& GetEyePosition() const { return m_eye; }

		const DirectX::SimpleMath::Vector3& GetTargetPosition() const { return m_target; }

		const DirectX::SimpleMath::Vector3& GetUpVector() const { return m_up; }

		//�I�[�o�[���C�h
	public:
		// ����������
		void Initialize() override;


		// �X�V����
		void Update(const float& elapsedTime) override;

		void Enter() override;

		void Exit() override;

	private:
		// �r���[�s����v�Z����
		void CalculateViewMatrix();

		// �v���W�F�N�V�����s����v�Z����
		void CalculateProjectionMatrix();


	};
}
