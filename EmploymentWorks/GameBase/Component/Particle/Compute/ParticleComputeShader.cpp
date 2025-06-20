//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2025/06/19
// <file>			ParticleComputeShader.cpp
// <�T�v>		�@�@�p�[�e�B�N���`��ɂ����R���s���[�g(�e�N�X�`���Z�b�g����Ă��Ȃ��Ƃ��ɗL��)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"ParticleComputeShader.h"
#include "Libraries/MyLib/BinaryFile.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ParticleComputeShader::ParticleComputeShader(DX::DeviceResources* device)
	:
	m_pDR{ device }
{
	Create();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ParticleComputeShader::~ParticleComputeShader()
{
}

/// <summary>
/// �쐬
/// </summary>
void ParticleComputeShader::Create()
{
	auto device = m_pDR->GetD3DDevice();
	// �V�F�[�_�Ƀf�[�^��n�����߂̃R���X�g�o�b�t�@�̐���
	D3D11_BUFFER_DESC bd = {};
	//ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);


	// �V�F�[�_���\�[�X�r���[�֓n�����߂̃e�N�X�`���T�v�쐬
	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = 512;
	texDesc.Height = 512;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	texDesc.SampleDesc.Count = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;

	// �f�o�C�X�ɏ���n���āA�쐬����
	device->CreateTexture2D(&texDesc, nullptr, &m_outputTexture);
	device->CreateUnorderedAccessView(m_outputTexture.Get(), nullptr, &m_outputUAV);
	device->CreateShaderResourceView(m_outputTexture.Get(), nullptr, &m_outputSRV);

	// �R���p�C�����ꂽ�V�F�[�_�t�@�C���̓ǂݍ���
	BinaryFile CSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleCS.cso");

	// �R���s���[�g�V�F�[�_�쐬
	if (FAILED(device->CreateComputeShader(CSData.GetData(), CSData.GetSize(), NULL, m_computeShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateComputeShader Failed.", NULL, MB_OK);
		return;
	}
}

/// <summary>
/// �C���[�W�摜�v�Z����
/// </summary>
void ParticleComputeShader::CalculateImage()
{
	ID3D11DeviceContext* context = m_pDR->GetD3DDeviceContext();
	// UAV�Z�b�g
	ID3D11UnorderedAccessView* uavs[1] = { m_outputUAV.Get() };
	context->CSSetUnorderedAccessViews(0, 1, uavs, nullptr);

	// �R���s���[�g�V�F�[�_���Z�b�g
	context->CSSetShader(m_computeShader.Get(), nullptr, 0);
	//context->CSSetShaderResources(0, 1, m_texture.GetAddressOf());
	// Dispatch
	context->Dispatch(static_cast<UINT>(516 / 16), static_cast<UINT>(516 / 16), 1);

	// ��n��
	ID3D11UnorderedAccessView* nullUAV[1] = { nullptr };
	context->CSSetUnorderedAccessViews(0, 1, nullUAV, nullptr);
	context->CSSetShader(nullptr, nullptr, 0);
}
