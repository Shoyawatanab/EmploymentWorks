#pragma once
#include "GameBase/Component.h"
#include "GameBase/Component/Components.h"



class ImageComponent : public Component
{

public:	
	//�C���v�b�g���C�A�E�g	
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4	windowSize;             //��ʃT�C�Y
		DirectX::SimpleMath::Vector4    Position;				//���W
		DirectX::SimpleMath::Vector4	Size;					//�傫��
		DirectX::SimpleMath::Vector4    Color;					//�F
		DirectX::SimpleMath::Vector4    CutRange;				//�؂���͈�
		DirectX::SimpleMath::Vector4    ViewRange;              //�\���͈�
		DirectX::SimpleMath::Vector4    FillAmount;				//�h��Ԃ���  x ���@y �c
	};

	//�`����
	enum class RenderKinds
	{
		NORMAL    //�ʏ�
		,CUSTOM	  //�J�X�^��
	};

public:

	//�摜�̎擾
	ID3D11ShaderResourceView* GetImage() { return m_texture.Get(); }

	//�؂���͈͂̃Z�b�g
	void SetCutRange(DirectX::SimpleMath::Vector4 range) { m_cutRange = range; }
	//�F�̃Z�b�g
	void SetColor(DirectX::SimpleMath::Vector4 color) { m_color = color; }
	//���̓h��Ԃ��ʁ@�O�`�P�܂ł͈̔�
	void SetHorizontalFillAmount(float fillAmount) { m_fillAmount.x = fillAmount; }
	//�\���͈͂̃Z�b�g
	void SetViewRange(DirectX::SimpleMath::Vector2 range) { m_viewRange.x = range.x; m_viewRange.y = range.y; }

	//�����̎擾
	float GetWidth() const;
	//�c���̎擾
	float GetHeight() const;
	//�J�X�^���`��֐��̓o�^
	void SetCustomRenderFunction(std::function<void()> customRender);

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
	//�ʏ�`��
	void NormalRender();
	//�J�X�^���`��
	void CustomRender();
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
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;


	//�摜�̑傫��
	int m_textureWidth;
	int	m_textureHeight;
	//�F
	DirectX::SimpleMath::Vector4 m_color;
	//�؂���͈�
	DirectX::SimpleMath::Vector4 m_cutRange;
	//�h��Ԃ��ʁ@x: ���@y :�c
	DirectX::SimpleMath::Vector4 m_fillAmount;
	//�\���͈�
	DirectX::SimpleMath::Vector4 m_viewRange;

	//�`��̎��
	RenderKinds m_renderKinds;

	//�ʕ`��
	std::function<void()> m_customRender;

};