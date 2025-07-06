#pragma once
#include "Game/Fade/IFade.h"

class BoomerangFadeIn : public IFade
{
public:

	//�R���X�^���g�o�b�t�@)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	time;
	};

	//�C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	//�t�F�[�h����
	static constexpr float MAX_TIME = 2.0f;

public:

	// �t�F�[�h�Ɏg�p����p�X
	static constexpr wchar_t VS_PATH[] = L"Resources/hlsl/cso/FadeVS.cso";
	static constexpr wchar_t GS_PATH[] = L"Resources/hlsl/cso/FadeGS.cso";
	static constexpr wchar_t PS_PATH[] = L"Resources/hlsl/cso/FadePS.cso";

	// �}�X�N�Ɏg�p����p�X
	static constexpr wchar_t MASK_VS_PATH[] = L"Resources/hlsl/cso/MaskVS.cso";
	static constexpr wchar_t MASK_GS_PATH[] = L"Resources/hlsl/cso/MaskGS.cso";
	static constexpr wchar_t MASK_PS_PATH[] = L"Resources/hlsl/cso/MaskPS.cso";

	// �t�F�[�h�̒x������
	static constexpr float CHANGE_SCENE_EDLAY = 1.0f;
	// �t�F�[�h�̎���
	static constexpr float FADE_TIME = 1.0f;
	// �t�F�[�h�̏����T�C�Y
	static constexpr float FADE_FIRST_SIZE = 1.25f;
	// �t�F�[�h�̍ő�T�C�Y
	static constexpr float FADE_MAX_SIZE = 6.0f;
	// �t�F�[�h�̂������l
	static constexpr float FADE_THRESHOLD = 0.7f;

public:

	//�R���X�g���N
	BoomerangFadeIn();
	//�f�X�g���N�^
	~BoomerangFadeIn() override;
	//�X�V����
	bool Update(const float& deltaTime) override;
	//�`��
	void Render() override;

	//��������
	void Enter() override;
	//��������
	void Exit() override;


private:
	//�V�F�[�_�[�쐬
	void CreateShader();
	// �t�F�[�h�ʂ��v�Z����
	float CalcrateFadeValue(float easing);
	// �^�����摜�̕`�揈��
	void DrawStencilImage();

private:
	//�R���X�g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	//	���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//�}�X�N�p���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_maskInputLayout;
	//	�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;

	//	�g�p���钸�_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	�g�p����s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//	�g�p����W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	//�}�X�N�p���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_maskVS;
	//�}�X�N�p�s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_maskPS;
	//�}�X�N�p�W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_maskGS;

	// ���[�h��ʂƂ��Ďg�p����e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �}�X�N�p�̃e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_stencilImage;
	// �^�����摜�݂̂̕`�挋�ʂ����摜
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_capture;
	// �^�����摜�݂̂̕`�挋�ʂ����摜�̃r���[
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_captureRTV;
	// �^�����摜�݂̂̕`�挋�ʂ����摜�̃V�F�[�_�[���\�[�X�r���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_captureSRV;
	// �o�ߎ���
	float m_totalTime;
};
