//--------------------------------------------------------------------------------------
//	File: Fade.h
//
//	�p�[�e�B�N���N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Fade.h"
#include "BinaryFile.h"
#include "DeviceResources.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

const float FADESPEED = 100.0f;

const float MAXFADETIME = 2.0f;

///	<summary>
///	�C���v�b�g���C�A�E�g
///	</summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> Fade::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3)+ sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

///	<summary>
///	�R���X�g���N�^
///	</summary>
Fade::Fade(ID3D11Device1* device, ID3D11DeviceContext* contect)
	:
	m_time{}
	,m_fadeState{}
	,m_isSceneChange{}
	,m_device{device}
	, m_context{contect}
{
	//������
	Initialize();
}

///	<summary>
///	�f�X�g���N�^
///	</summary>
Fade::~Fade()
{
}

void Fade::Initialize()
{

	//	�V�F�[�_�[�̍쐬
	CreateShader();

	//	�v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(m_context);

	m_states = std::make_unique<DirectX::CommonStates>(m_device);

	m_currentPS = m_normalFadeInPS.Get();

	m_fadeState = FadeState::None;
	m_time = 0;

	m_maxFadeTime = MAXFADETIME;

	m_isSceneChange = false;


}

void Fade::Update(float elapsdTime)
{
	//�t�F�[�h������Ȃ����
	if (m_fadeState == FadeState::None)
	{
		return;
	}

	if (m_time >= MAXFADETIME)
	{

		switch (m_fadeState)
		{
			case Fade::None:
				break;
			case Fade::FadeIn:
				m_isSceneChange = true;

				break;
			case Fade::FadeOut:
				m_isSceneChange = false;

				break;
			default:
				break;
		}


		m_fadeState = FadeState::None;

		return;
	}


 	m_time += elapsdTime ;
	

}

//�ʏ�t�F�[�h�̊J�n�֐�
void Fade::StartNormalFadeIn()
{

	m_fadeState = FadeState::FadeIn;

	m_time = 0;

	m_currentPS = m_normalFadeInPS.Get();

}



void Fade::StartNormalFadeOut()
{
	m_fadeState = FadeState::FadeOut;
	m_time = 0;

	m_currentPS = m_normalFadeOutPS.Get();
}

///	<summary>
///	Shader�쐬�����������������֐�
///	</summary>
void Fade::CreateShader()
{

	//	�R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/FadeVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/FadeGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/NormalFadeInPS.cso");

	BinaryFile PSData2 = BinaryFile::LoadFile(L"Resources/Shaders/NormalFadeOutPS.cso");


	//	�C���v�b�g���C�A�E�g�̍쐬
	m_device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	//	���_�V�F�[�_�쐬
	if (FAILED(m_device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_currentVS.ReleaseAndGetAddressOf())))
	{//	�G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	//	�W�I���g���V�F�[�_�쐬
	if (FAILED(m_device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_currentGS.ReleaseAndGetAddressOf())))
	{//	�G���[
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}

	//	�s�N�Z���V�F�[�_�쐬
	if (FAILED(m_device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_normalFadeInPS.ReleaseAndGetAddressOf())))
	{//	�G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	//	�s�N�Z���V�F�[�_�쐬
	if (FAILED(m_device->CreatePixelShader(PSData2.GetData(), PSData2.GetSize(), NULL, m_normalFadeOutPS.ReleaseAndGetAddressOf())))
	{//	�G���[
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
	m_device->CreateBuffer(&bd, nullptr, &m_CBuffer);


}

///	<summary>
///	�`��֐�
///	</summary>
///	<param name="view">�r���[�s��</param>
///	<param name="proj">�ˉe�s��</param>
void Fade::Render()
{

	//	���_���(�|���S���̂S���_�̍��W���j
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(0.0f,  0.0f, 0.0f), DirectX::SimpleMath::Vector4::One, DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
	};

	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.matView = DirectX::SimpleMath::Matrix::Identity;
	cbuff.matProj = DirectX::SimpleMath::Matrix::Identity;
	cbuff.matWorld = DirectX::SimpleMath::Matrix::Identity;
	cbuff.Diffuse = DirectX::SimpleMath::Vector4(1, 1, 1, 1);
	cbuff.time = DirectX::SimpleMath::Vector4(m_time, m_maxFadeTime, 1, 1);

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	m_context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	m_context->VSSetConstantBuffers(0, 1, cb);
	m_context->GSSetConstantBuffers(0, 1, cb);
	m_context->PSSetConstantBuffers(0, 1, cb);

	//	�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	m_context->PSSetSamplers(0, 1, sampler);


	//	�������`��w��
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	//	�������菈��
	m_context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	m_context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	//	�J�����O�͍�����
	m_context->RSSetState(m_states->CullNone());

	//	�V�F�[�_���Z�b�g����
	m_context->VSSetShader(m_currentVS.Get(), nullptr, 0);
	m_context->GSSetShader(m_currentGS.Get(), nullptr, 0);
	m_context->PSSetShader(m_currentPS.Get(), nullptr, 0);

	//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	for (int i = 0; i < m_texture.size(); i++)
	{
		m_context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	//	�C���v�b�g���C�A�E�g�̓o�^
	m_context->IASetInputLayout(m_inputLayout.Get());

	//	�|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_batch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->GSSetShader(nullptr, nullptr, 0);
	m_context->PSSetShader(nullptr, nullptr, 0);

}


