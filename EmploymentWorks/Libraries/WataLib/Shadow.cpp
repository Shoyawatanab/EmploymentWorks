/*
	@file	Shadow.cpp
	@brief	�e�|���S����\������N���X
*/
#include "pch.h"
#include "Shadow.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
WataLib::Shadow::Shadow()
	:
	m_texture{},
	m_primitiveBatch{},
	m_basicEffect{},
	m_inputLayout{},
	m_depthStencilState{}
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="device">�f�o�C�X</param>
/// <param name="context">�R���e�L�X�g</param>
/// <param name="states">�R�����X�e�[�g</param>
void WataLib::Shadow::Initialize(
	ID3D11Device* device,
	ID3D11DeviceContext* context,
	DirectX::CommonStates* states
)
{
	using namespace DirectX;

	assert(device);
	assert(context);
	assert(states);

	// �x�[�V�b�N�G�t�F�N�g��ݒ肷��
	m_basicEffect = std::make_unique<BasicEffect>(device);
	m_basicEffect->SetVertexColorEnabled(false);
	m_basicEffect->SetTextureEnabled(true);
	m_basicEffect->SetLightingEnabled(false);

	// ���̓��C�A�E�g��ݒ肷��
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionTexture>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);

	// �v���~�e�B�u�o�b�`�𐶐�����
	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	// �摜��ǂݍ���
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(
			device,
			L"Resources/Textures/Shadow.png",
			nullptr,
			m_texture.ReleaseAndGetAddressOf()
		)
	);

	// �[�x�X�e���V���o�b�t�@��ݒ肷��
	D3D11_DEPTH_STENCIL_DESC desc{};

	// �e�F�`���̃X�e���V���o�b�t�@�ƎQ�ƒl�������Ƃ��e��`�悷��
	desc.DepthEnable = true;									// �[�x�e�X�g���s��
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;			// �[�x�o�b�t�@���X�V����
	desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;				// �[�x�l�ȉ��Ȃ�X�V����

	desc.StencilEnable = true;									// �X�e���V���e�X�g���s��
	desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;		// 0xff
	desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;	// 0xff

	// �\��
	desc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;		// �Q�ƒl�ƃX�e���V���l�����l�Ȃ�
	desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;		// OK�@�������Ȃ�
	desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;		// NG�@�������Ȃ�
	desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;	// NG�@�������Ȃ�

	// ���ʂ������ݒ�
	desc.BackFace = desc.FrontFace;

	// �[�x�X�e���V���X�e�[�g���쐬����
	device->CreateDepthStencilState(&desc, m_depthStencilState.ReleaseAndGetAddressOf());
}

/// <summary>
/// �`��
/// </summary>
/// <param name="context">�R���e�L�X�g</param>
/// <param name="states">�R�����X�e�[�g</param>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
/// <param name="position">���W</param>
/// <param name="radius">���a</param>
void WataLib::Shadow::Render(
	ID3D11DeviceContext* context,
	DirectX::CommonStates* states,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection,
	const DirectX::SimpleMath::Vector3& position,
	float radius
)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	assert(context);
	assert(states);

	// �A���t�@�u�����h��K�p����
	context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xffffffff);

	// �[�x�X�e���V���X�e�[�g��K�p����
	context->OMSetDepthStencilState(m_depthStencilState.Get(), 1);	// �Q�ƒl�F1

	// �J�����O��ݒ肷��
	context->RSSetState(states->CullCounterClockwise());

	// �e�N�X�`���T���v����K�p����
	ID3D11SamplerState* sampler = { states->LinearClamp() };
	context->PSSetSamplers(0, 1, &sampler);

	// ���̓��C�A�E�g��K�p����
	context->IASetInputLayout(m_inputLayout.Get());

	// �G�t�F�N�g��ݒ肵�K�p����
	m_basicEffect->SetWorld(Matrix::Identity);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(projection);
	m_basicEffect->SetTexture(m_texture.Get());
	m_basicEffect->Apply(context);

	// �e�|���S���̒��_�����`����
	VertexPositionTexture vertices[] = {
		VertexPositionTexture(Vector3::Zero,Vector2(0.0f, 0.0f)),
		VertexPositionTexture(Vector3::Zero,Vector2(1.0f, 0.0f)),
		VertexPositionTexture(Vector3::Zero,Vector2(0.0f, 1.0f)),
		VertexPositionTexture(Vector3::Zero,Vector2(1.0f, 1.0f)),
	};

	// �e�|���S���̃C���f�b�N�X�����`����FDrawIndexed�ŕ`�悷��Ƃ��ɕK�v
	uint16_t indexes[] = { 0, 1, 2, 1, 3, 2 };

	// �e�|���S���̒��_����ݒ肷��
	vertices[0].position = Vector3(-radius, 0.01f, -radius) + position;
	vertices[1].position = Vector3( radius, 0.01f, -radius) + position;
	vertices[2].position = Vector3(-radius, 0.01f,  radius) + position;
	vertices[3].position = Vector3( radius, 0.01f,  radius) + position;

	// �e�|���S����`�悷��
	m_primitiveBatch->Begin();

	// DrawIndexed�ŕ`�悷��@
	m_primitiveBatch->DrawIndexed(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		indexes,
		_countof(indexes),
		vertices,
		_countof(vertices)
	);

	//// DrawQuad�ŕ`�悷��A
	//m_primitiveBatch->DrawQuad(vertices[0], vertices[1], vertices[3], vertices[2]);

	m_primitiveBatch->End();
}
