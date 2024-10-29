/*
	@file	ResultScene.h
	@brief	�^�C�g���V�[���N���X
*/
#pragma once
#include "IScene.h"

// �O���錾
class CommonResources;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class ResultScene final :
    public IScene
{
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

	// �e�N�X�`��
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_numberTexture;

	// �e�N�X�`���̔����̑傫��
	std::vector<DirectX::SimpleMath::Vector2> m_numberTexCenter;


	// �V�[���`�F���W�t���O
	bool m_isChangeScene;
	DirectX::SimpleMath::Matrix m_projection;
	DirectX::SimpleMath::Matrix* m_view;


public:
    ResultScene();
    ~ResultScene() override;

    void Initialize(CommonResources* resources) override;
    void Update(float elapsedTime)override;
    void Render() override;
    void Finalize() override;

    SceneID GetNextSceneID() const;



	void CreateTex(const wchar_t* szFileName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& tex, DirectX::SimpleMath::Vector2& texCenter);

	void TexRender(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Tex, DirectX::SimpleMath::Vector2& Center, DirectX::SimpleMath::Vector2 Pos, float Scale);
};
