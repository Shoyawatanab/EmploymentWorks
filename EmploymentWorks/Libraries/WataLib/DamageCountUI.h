/*
	@file	DamageCountUI.h
	@brief	�^�C�g���V�[���N���X
*/
#pragma once


// �O���錾
class CommonResources;
class UserInterface;
class DrawNumber;


namespace WataLib
{
	class DamageCountUI final
	{
	public:
		//�����Ԋu
		static constexpr float DIGITWIDTH = 4.5f;
		//��������
		static constexpr float MAXTIME = 1.0f;

	public:

		const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }

		void SetPosition(const DirectX::SimpleMath::Vector3& Pos);

		void SetScale(const DirectX::SimpleMath::Vector2& scale);

		float GetRotate() const  { return m_rotate; }

		void SetRotate(const float& rotate);

		const DirectX::SimpleMath::Vector2& GetCenter() { return m_texCenter; }

		void SetDamage(const int& damage);

		void SetScreenPosition(const DirectX::SimpleMath::Vector2& position);

		void SetIsActive(const bool& isActive) { m_isActive = isActive; }

		bool GetIsActive() const { return m_isActive; }
		
	public:
		//�R���X�g���N�^
		DamageCountUI(CommonResources* resources);
		//�f�X�g���N�^
		~DamageCountUI();
		//������
		void Initialize();

		// �X�V����
		void Update(const float& elapsedTime);
		//�`��
		void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

		void Finalize();

	private:

		//�摜�̓ǂݍ���
		std::unique_ptr<UserInterface> LoadTexture(std::string key
			, DirectX::SimpleMath::Vector2 position
			, DirectX::SimpleMath::Vector2 scale
		);

		//���[���h���W���X�N���[�����W�ɕϊ�
		DirectX::SimpleMath::Vector2 WorldToScreen(const DirectX::SimpleMath::Vector3& worldPos,
			const DirectX::SimpleMath::Matrix& worldMatrix,
			const DirectX::SimpleMath::Matrix& viewMatrix,
			const DirectX::SimpleMath::Matrix& projectionMatrix,
			int screenWidth, int screenHeight);


	private:
		// ���ʃ��\�[�X
		CommonResources* m_commonResources;
		// �e�N�X�`��
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		// �e�N�X�`���̔����̑傫��
		DirectX::SimpleMath::Vector2 m_texCenter;
		//�摜�̍��W
		DirectX::SimpleMath::Vector3 m_position;
		//�摜�̑傫��
		DirectX::SimpleMath::Vector2 m_scale;
		//�摜�̉�]�p�x
		float m_rotate;
		//�w�i
		std::unique_ptr<UserInterface> m_backGraund;
		//�ԍ�
		std::unique_ptr<DrawNumber> m_numberUI;
		//�_���[�W
		int m_damage;
		//�X�N���[�����W
		DirectX::SimpleMath::Vector2 m_screenPosition;
		//�L�����ǂ���
		bool m_isActive;

		//1����
		std::vector<std::pair<int,DirectX::SimpleMath::Vector2>> m_digitNumber;
		//����
		float m_time;

	};
}