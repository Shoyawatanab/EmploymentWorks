/*
	@file	Texture.h
	@brief	�^�C�g���V�[���N���X
*/
#pragma once


// �O���錾
class CommonResources;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

namespace mylib
{
	class Texture final
	{
	public:

		void SetPosition(DirectX::SimpleMath::Vector2 Pos) { m_position = Pos; }

		void SetScale(float scale) { m_scale = scale; }

		float GetRotate() { return m_rotate; }

		void SetRotate(float rotate) { m_rotate = rotate; }

	private:

		// ���ʃ��\�[�X
		CommonResources* m_commonResources;

		// �X�v���C�g�o�b�`
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

		// �X�v���C�g�t�H���g
		std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

		// �e�N�X�`��
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

		// �e�N�X�`���̔����̑傫��
		DirectX::SimpleMath::Vector2 m_texCenter;
		//�摜�̍��W
		DirectX::SimpleMath::Vector2 m_position;
		//�摜�̑傫��
		float m_scale;
		//�摜�̉�]�p�x
		float m_rotate;

	public:
		Texture();
		~Texture();

		void Initialize(CommonResources* resources, const wchar_t* szFileName, DirectX::SimpleMath::Vector2 Pos, float scale);
		void Render();
		void Finalize();



	};
}