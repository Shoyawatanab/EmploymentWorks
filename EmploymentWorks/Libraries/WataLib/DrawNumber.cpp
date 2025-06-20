//--------------------------------------------------------------------------------------
// File: DrawNumber.h
//
// ���[�U�[�C���^�[�t�F�[�X�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "DrawNumber.h"

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


/// <summary>
/// �C���v�b�g���C�A�E�g
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> DrawNumber::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
DrawNumber::DrawNumber()
	:m_pDR(nullptr)
	, m_textureHeight(0)
	, m_textureWidth(0)
	, m_texture(nullptr)
	, m_res(nullptr)
	, m_scale(DirectX::SimpleMath::Vector2::One)
	, m_position(DirectX::SimpleMath::Vector2::Zero)
	, m_renderRatio(1.0f)
	, m_renderRatioOffset(0.0f)
	, m_alphaValue{ 1.0f }
	,m_isActive{true}
	,m_offsetPosition{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DrawNumber::~DrawNumber()
{
}

/// <summary>
/// �e�N�X�`�����\�[�X�ǂݍ��݊֐�
/// </summary>
/// <param name="path">���΃p�X(Resources/Textures/�E�E�E.png�Ȃǁj</param>
void DrawNumber::LoadTexture(const wchar_t* path)
{
	//	�P�q�摜��ǂݍ���
	/*HRESULT result; = DirectX::CreateWICTextureFromFile(m_pDR->GetD3DDevice(), L"Resources/Textures/yoshiko.jpg", m_yoshiRes.ReleaseAndGetAddressOf(), m_yoshiTexture.ReleaseAndGetAddressOf());
	Microsoft::WRL::ComPtr<ID3D11Texture2D> yoshiTex;
	DX::ThrowIfFailed(m_yoshiRes.As(&yoshiTex));*/

	//	�w�肳�ꂽ�摜��ǂݍ���
	DirectX::CreateWICTextureFromFile(m_pDR->GetD3DDevice(), path, m_res.ReleaseAndGetAddressOf(), m_texture.ReleaseAndGetAddressOf());
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(m_res.As(&tex));

	//	�ǂݍ��񂾉摜�̏����擾����
	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	//	�ǂݍ��񂾉摜�̃T�C�Y���擾����
	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;



}

/// <summary>
/// �����֐�
/// </summary>
/// <param name="pDR">���[�U�[���\�[�X�����玝���Ă���</param>
void DrawNumber::Create(DX::DeviceResources* pDR
	, const wchar_t* path
	, const DirectX::SimpleMath::Vector2& position
	, const DirectX::SimpleMath::Vector2& scale
	)
{
	using namespace DirectX;

	m_pDR = pDR;
	auto device = pDR->GetD3DDevice();
	m_position = position;
	m_initialPosition = position;
	m_scale = scale;
	m_initialScale = scale;

	//�V�F�[�_�[�̍쐬
	CreateUIShader();

	//	�摜�̓ǂݍ���
	LoadTexture(path);

	//	�v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(pDR->GetD3DDeviceContext());

	m_states = std::make_unique<CommonStates>(device);


}

void DrawNumber::SetScale(const DirectX::SimpleMath::Vector2& scale)
{
	m_scale = scale;
}
void DrawNumber::SetPosition(const DirectX::SimpleMath::Vector2& position)
{
	m_position = position;
}



void DrawNumber::SetRenderRatio(const float& ratio)
{
	m_renderRatio = ratio;
}



/// <summary>
/// �V�F�[�_�[�̍쐬
/// </summary>
void DrawNumber::CreateUIShader()
{
	auto device = m_pDR->GetD3DDevice();

	//	�R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/NumberVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/NumberGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/NumberPS.cso");

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
void DrawNumber::Render(const int& number , const DirectX::SimpleMath::Vector2& offsetPosition)
{
	using namespace DirectX;

	//�L�����ǂ���
	if (!m_isActive)
	{
		return;
	}


	auto context = m_pDR->GetD3DDeviceContext();
	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(
			 SimpleMath::Vector3(m_scale.x, m_scale.y, 4)
			,SimpleMath::Vector4(m_position.x + offsetPosition.x, m_position.y + offsetPosition.y, static_cast<float>(m_textureWidth/10), static_cast<float>(m_textureHeight))
			,SimpleMath::Vector2(m_renderRatio - m_renderRatioOffset,0))
	};

	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.windowSize = SimpleMath::Vector4(Screen::WIDTH, Screen::HEIGHT, 1, 1);
	cbuff.Diffuse = SimpleMath::Vector4(static_cast<float>(number), 1, 1, 1);

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


