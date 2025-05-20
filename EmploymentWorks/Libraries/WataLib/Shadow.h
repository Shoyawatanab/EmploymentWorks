/*
	@file	Shadow.h
	@brief	�e�|���S����\������N���X
*/
#pragma once



namespace WataLib
{
	class Shadow
	{

	public:
		//�R���X�g���N�^
		Shadow();
		//�f�X�g���N�^
		~Shadow() = default;

		// ����������
		void Initialize(
			ID3D11Device* device,
			ID3D11DeviceContext* context,
			DirectX::CommonStates* states
		);

		// �`�悷��
		void Render(
			ID3D11DeviceContext* context,
			DirectX::CommonStates* states,
			const DirectX::SimpleMath::Matrix& view,
			const DirectX::SimpleMath::Matrix& projection,
			const DirectX::SimpleMath::Vector3& position,
			float radius = 0.7f
		);

	private:
		// �e�N�X�`��
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

		// �v���~�e�B�u�o�b�`
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;

		// �x�[�V�b�N�G�t�F�N�g
		std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

		// ���̓��C�A�E�g
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

		// �[�x�X�e���V���X�e�[�g
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;


	};
}