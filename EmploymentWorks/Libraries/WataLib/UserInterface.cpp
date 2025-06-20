//--------------------------------------------------------------------------------------
// File: UserInterface.h
//
// ���[�U�[�C���^�[�t�F�[�X�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "UserInterface.h"

#include "Libraries/MyLib/BinaryFile.h"
#include "GameBase/Common/Commons.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>
#include "GameBase/Screen.h"
#include "GameBase/GameResources.h"

using namespace DirectX;

/// <summary>
/// �C���v�b�g���C�A�E�g
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> UserInterface::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
UserInterface::UserInterface()
	:
	m_commonResources{}
	, m_textureHeight(0)
	, m_textureWidth(0)
	, m_texture(nullptr)
	, m_res(nullptr)
	, m_scale(SimpleMath::Vector2::One)
	, m_position(SimpleMath::Vector2::Zero)
	, m_renderRatio(1.0f)
	, m_renderRatioOffset(0.0f)
	, m_alphaValue{ 1.0f }
	,m_isActive{true}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UserInterface::~UserInterface()
{
}


/// <summary>
/// �摜�̓ǂݍ���
/// </summary>
/// <param name="key">�L�[</param>
void UserInterface::LoadTexture(std::string key)
{

	//�摜�̎擾
	m_texture = GameResources::GetInstance()->GetTexture(key);

	//�V�F�[�_�[���\�[�X�r���[����摜���̎擾
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	m_texture->GetResource(&resource);

	//���\�[�X��Texture2D�ɃL���X�g
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(resource.As(&tex));

	//�摜�����擾
	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	//�摜�̃T�C�Y���擾
	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;
	

}

/// <summary>
/// ����
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="key">�L�[</param>
/// <param name="position">���W</param>
/// <param name="scale">�傫��</param>
void UserInterface::Create(CommonResources* resources, std::string key, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale)
{
	m_commonResources = resources;
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	m_position = position;
	m_initialPosition = position;
	m_scale = scale;
	m_initialScale = scale;

	//�V�F�[�_�[�̍쐬
	CreateUIShader();

	//	�摜�̓ǂݍ���
	LoadTexture(key);

	//	�v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);

	m_states = std::make_unique<CommonStates>(device);

}

void UserInterface::SetScale(const DirectX::SimpleMath::Vector2& scale)
{
	m_scale = scale;
}
void UserInterface::SetPosition(const DirectX::SimpleMath::Vector2& position)
{
	m_position = position;
}



void UserInterface::SetRenderRatio(const float& ratio)
{
	m_renderRatio = ratio;
}



/// <summary>
/// �V�F�[�_�[�̍쐬
/// </summary>
void UserInterface::CreateUIShader()
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	//	�R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/UIVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/UIGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/UIPS.cso");

	//	�C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	//	���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{//	�G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	//	�W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	//	�s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	//	�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);
}



/// <summary>
/// �`��֐�
/// </summary>
void UserInterface::Render()
{
	//�L�����ǂ���
	if (!m_isActive)
	{
		return;
	}

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	// ���_���
	// Position.xy	:�g�k�p�X�P�[��
	// Position.z	:�A���J�[�^�C�v(0�`8)�̐����Ŏw��
	// Color.xy�@	:�A���J�[���W(�s�N�Z���w��:1280 �~720)
	// Color.zw		:�摜�T�C�Y
	// Tex.xy		:�E�B���h�E�T�C�Y�i�o�b�t�@�������B������͖��g�p�j
	VertexPositionColorTexture vertex[1] = {
		VertexPositionColorTexture(
			 SimpleMath::Vector3(m_scale.x, m_scale.y, ANCHOR::MIDDLE_CENTER)
			,SimpleMath::Vector4(m_position.x, m_position.y, static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight))
			,SimpleMath::Vector2(m_renderRatio - m_renderRatioOffset,0))
	};

	//	��������L�̐ݒ�l�ɂ́AWorld��View�Ȃǂ�3D��Ԃ���ϊ����邽�߂̌v�Z����؂��Ȃ����߁A
	//	�X�N���[�����W�Ƃ��ĕ`�悳���

	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.windowSize = SimpleMath::Vector4(Screen::WIDTH, Screen::HEIGHT, 1, 1);
	cbuff.diffuse = SimpleMath::Vector4(1, 1, 1, m_alphaValue);

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);


	//	�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//	�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);


	//	�������`��w��
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	//	�������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	//	�J�����O�͍�����
	context->RSSetState(m_states->CullNone());

	//	�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());


	//	�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	//	�|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}


