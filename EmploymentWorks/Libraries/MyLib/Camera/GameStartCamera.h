/*
	@file	GameStartCamera.h
	@brief	TPS�J�����N���X
*/
#pragma once
#include "Interface/IGameCamera.h"

class Player;



namespace mylib
{
	class GameStartCamera :public IGameCamera
	{
	private:



	public:
		// getter
		const DirectX::SimpleMath::Matrix& GetViewMatrix() override { return m_view; }

		const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }

		const DirectX::SimpleMath::Vector3& GetEyePosition() const { return m_eye; }

		const DirectX::SimpleMath::Vector3& GetTargetPosition() const { return m_target; }

		const DirectX::SimpleMath::Vector3& GetUpVector() const { return m_up; }

		DirectX::SimpleMath::Quaternion GetRotationX() { return m_rotationX; }


		void SetCameraEndPos(DirectX::SimpleMath::Vector3 endPos) { m_cameraEndPos = endPos; }

		const float& GetLerpTime() { return m_lerpTime; }

	private:
		// �^�[�Q�b�g����̃f�t�H���g����
		const float CAMERA_DISTANCE = 7.0f;
		const float CAMERA_HIGHT = 5.0f;

		// ��p
		const float FOV = DirectX::XMConvertToRadians(45.0f);

		// �߂����e��
		const float NEAR_PLANE = 1.0f;

		// �������e��
		const float FAR_PLANE = 100.0f;

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


		float m_lerpTime;


		//�J�����̊p�x
		float m_angle;
		//�J�����̍���
		float m_height;
		//
		float m_distanceFromTarget;

		DirectX::SimpleMath::Vector3 m_cameraEndPos;
		DirectX::SimpleMath::Vector3 m_endTarget;

	public:
		// �R���X�g���N�^
		GameStartCamera(Player* Player);

		// �f�X�g���N�^
		~GameStartCamera() = default;

		// �X�V����

		//�I�[�o�[���C�h
	public:

		void Initialize() override;


		void Update(const float& elapsedTime);

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
