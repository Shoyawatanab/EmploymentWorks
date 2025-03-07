/*
	@file	GameEndCamera.h
	@brief	TPS�J�����N���X
	�G��|������̃J����
*/
#pragma once
#include "Game/Interface/ICamera.h"
#include "Game/Interface/ICharacter.h"

class EnemyManager;

namespace WataLib
{
	class GameEndCamera :public ICamera
	{

	public:
		// getter
		const DirectX::SimpleMath::Matrix& GetViewMatrix() override { return m_view; }

		const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }

		const DirectX::SimpleMath::Vector3& GetEyePosition() const { return m_eye; }

		const DirectX::SimpleMath::Vector3& GetTargetPosition() const { return m_target; }

		const DirectX::SimpleMath::Vector3& GetUpVector() const { return m_up; }

		void SetCharacter(ICharacter* character) { m_character = character; }

	public:
		// �R���X�g���N�^
		GameEndCamera();

		// �f�X�g���N�^
		~GameEndCamera() = default;

		void Initialize(CommonResources* resources) override;


		void Update(const float& elapsedTime);

		void Enter() override;

		void Exit() override;

		//�`��
		void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;


		void AddPointer(EnemyManager* enemyManger);



	private:
		// �r���[�s����v�Z����
		void CalculateViewMatrix();

		// �v���W�F�N�V�����s����v�Z����
		void CalculateProjectionMatrix();

		// �J�������W���v�Z����
		void CalculateEyePosition();

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


		//�J�����̊p�x
		float m_angle;

		DirectX::SimpleMath::Quaternion m_rotation;

		ICharacter* m_character;

		EnemyManager* m_enemyManager;


	};
}
