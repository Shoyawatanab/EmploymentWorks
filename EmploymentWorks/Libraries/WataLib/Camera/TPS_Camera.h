/*
	@file	TPS_Camera.h
	@brief	TPS�J�����N���X
*/
#pragma once
#include "Game/Interface/ICamera.h"
#include "Game/Interface/IObserver.h"

// �O���錾
class CommonResources;
class Player;

namespace WataLib
{
	class Mouse;
}

namespace WataLib
{
	class TPS_Camera :public ICamera ,public IObserver<GameMessageType>
	{
	private:
		//�}�E�X���x�̍\����
		struct MouseSensitivity 
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

		//�f�o�b�N�p
		const POINT GetAngle() { return m_angle; }
	public:
		// �^�[�Q�b�g����̃f�t�H���g����
		const float CAMERA_DISTANCE = 4.0f;
		const float CAMERA_HIGHT = 0.0f;

		// ��p
		const float FOV = DirectX::XMConvertToRadians(45.0f);

		// �߂����e��
		const float NEAR_PLANE = 1.0f;

		// �������e��
		const float FAR_PLANE = 100.0f;

		static constexpr float SHAKETIME = 2.0f;

		

		//Getter Setter
	public:
		// getter
		const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }

		const DirectX::SimpleMath::Vector3& GetEyePosition() const { return m_eye; }

		void SetEyePosition(DirectX::SimpleMath::Vector3 pos)
		{
			m_eye = pos; 	// �J�������W���v�Z����
			// �r���[�s����X�V����
			CalculateViewMatrix();
		}

		const DirectX::SimpleMath::Vector3& GetTargetPosition() const { return m_target; }

		const DirectX::SimpleMath::Vector3& GetUpVector() const { return m_up; }

		DirectX::SimpleMath::Quaternion GetRotationX() { return m_rotationX; }

		DirectX::SimpleMath::Vector3 GetCameraForward() { return m_forward; }

		//////
		//
		void SetZoomState(ZoomState state) { m_zoomState = state; }
		const DirectX::SimpleMath::Matrix& GetViewMatrix() override { return m_view; }


	public:
		// �R���X�g���N�^
		TPS_Camera();

		// �f�X�g���N�^
		~TPS_Camera() override ;

		// ����������
		void Initialize(CommonResources* resources) override;
		// �X�V����
		void Update(const float& elapsedTime) override;
		//�`��
		void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;

		void Enter() override;

		void Exit() override;


		//�N���X�ɕK�v�ȏ��i�|�C���^�j��o�^����
		void AddPointer(Player* Player);

		// �r���[�s����v�Z����
		void CalculateViewMatrix();

		// �v���W�F�N�V�����s����v�Z����
		void CalculateProjectionMatrix();

		// �J�������W���v�Z����
		void CalculateEyePosition();
		//�ʒm���ɌĂ΂��֐�
		void Notify(const Telegram<GameMessageType>& telegram)  override;
		

	private:
		//�h��
		void Shake(const float& elapsedTime);

	private:
		//�錾
		Player* m_player;
		std::unique_ptr<WataLib::Mouse> m_mouse;

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


		DirectX::SimpleMath::Quaternion m_rotationX;

		//��]�p�x
		POINT m_angle;
		//�}�E�X���x
		MouseSensitivity m_mouseSensitivity;

		float m_lerpTime;

		//�\�������̃J�����̓�������
		DirectX::SimpleMath::Vector3 m_moveEye;

		ZoomState m_zoomState;

		DirectX::SimpleMath::Vector3 m_forward;

		//�J������h�炷���ǂ���
		bool m_isShake;
		//�h��̎���
		float m_shaleTime;
		//�h��̋���
		float m_shakePower;
		//�h��̍��W
		DirectX::SimpleMath::Vector3 m_shakePosition;



	};
}
