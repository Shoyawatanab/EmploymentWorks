#include "pch.h"
#include "RoundShadowComponent.h"
#include "GameBase/Actor.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Managers.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Camera/Camera.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="owner">���L��</param>
/// <param name="radius">���a</param>
RoundShadowComponent::RoundShadowComponent(Actor* owner, float radius)
	:
	Component(owner)
	,m_radius{radius}
{
	using namespace DirectX;

	//�}�l�[�W���[�ɒǉ�
	GetActor()->GetScene()->GetRenderMangaer()->AddRoundShadow(this);

	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

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
/// �f�X�g���N�^
/// </summary>
RoundShadowComponent::~RoundShadowComponent()
{
}

/// <summary>
/// �`��
/// </summary>
/// <param name="camera">�J����</param>
void RoundShadowComponent::Render(const Camera& camera)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = CommonResources::GetInstance()->GetCommonStates();


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
	m_basicEffect->SetView(camera.GetViewMatrix());
	m_basicEffect->SetProjection(camera.GetProjectionMatrix());
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

	auto position = GetActor()->GetTransform()->GetWorldPosition();
	//���ɍ��킹��
	position.y = 0.1f;

	// �e�|���S���̒��_����ݒ肷��
	vertices[0].position = Vector3(-m_radius, 0.01f, -m_radius) + position;
	vertices[1].position = Vector3(m_radius, 0.01f, -m_radius) + position;
	vertices[2].position = Vector3(-m_radius, 0.01f, m_radius) + position;
	vertices[3].position = Vector3(m_radius, 0.01f, m_radius) + position;

	// �e�|���S����`�悷��
	m_primitiveBatch->Begin();

	// DrawIndexed�ŕ`�悷��
	m_primitiveBatch->DrawIndexed(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		indexes,
		_countof(indexes),
		vertices,
		_countof(vertices)
	);


	m_primitiveBatch->End();

}


