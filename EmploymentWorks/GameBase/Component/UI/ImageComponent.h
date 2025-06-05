#pragma once
#include "GameBase/Component.h"


//UI�̃A���J�[�|�C���g�̗񋓐�
enum ANCHOR
{
	TOP_LEFT = 0,
	TOP_CENTER,
	TOP_RIGHT,

	MIDDLE_LEFT,
	MIDDLE_CENTER,
	MIDDLE_RIGHT,

	BOTTOM_LEFT,
	BOTTOM_CENTER,
	BOTTOM_RIGHT

};

class ImageComponent : public Component
{

public:	
	//�C���v�b�g���C�A�E�g	
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4	windowSize;
		DirectX::SimpleMath::Vector4    diffuse;
	};

public:

	//�摜�̎擾
	ID3D11ShaderResourceView* GetImage() { return m_texture.Get(); }

	//
	void SetRenderRatio(const float& ratio) { m_renderRatio = ratio; }
	//
	float GetRenderRatio() const { return m_renderRatio; }
	//
	void SetRenderRatioOffset(const float& offset) { m_renderRatioOffset = offset; };
	//
	float GetRenderRatioOffset() const { return m_renderRatioOffset; }
	//�����x�̃Z�b�g
	void SetAlphaValue(const float& value) { m_alphaValue = value; }
	//�����x�̎擾
	float GetAlphaValue() const { return m_alphaValue; }


public:
	//�R���X�g���N�^
	ImageComponent(Actor* owner,std::string textureName);
	//�f�X�g���N�^
	~ImageComponent() override;

	//�`��
	void Render();

private:

	//�摜�̓ǂݍ���
	void LoadTexture(std::string textureName);

private:
	//�摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;


	//�摜�̑傫��
	int m_textureWidth, m_textureHeight;
	float m_renderRatio;
	float m_renderRatioOffset;

	//�摜�S�̂̓����x
	float m_alphaValue;


};