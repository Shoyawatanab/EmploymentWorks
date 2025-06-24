#pragma once
#include "Game/Fade/IFade.h"

class NormalFadeOut : public IFade
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



public:

	//�R���X�g���N
	NormalFadeOut();
	//�f�X�g���N�^
	~NormalFadeOut() override;
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
	void CreateShader(ID3D11Device1* device, ID3D11DeviceContext* context);

private:
	//�R���X�g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	//	���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	�g�p���钸�_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	�g�p����s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//	�g�p����W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
	//����
	float m_time;

};
