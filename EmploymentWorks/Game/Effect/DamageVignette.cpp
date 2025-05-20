/*
	@file	DamageVignette.cpp
	@brief	��ʓI�ȃV�[���N���X
*/
#include "pch.h"
#include "DamageVignette.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/MyLib/BinaryFile.h"




///	<summary>
///	�C���v�b�g���C�A�E�g
///	</summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> DamageVignette::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
DamageVignette::DamageVignette(CommonResources* resources)
	:
	m_commonResources{resources},
	m_position{},
	m_scale{}
	,m_isActive{false}
	,m_alpha{}
	,m_damageCount{}
	,m_CBuffer{}
	,m_inputLayout{}
	,m_batch{}
	,m_vs{}
	,m_ps{}
	,m_gs{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DamageVignette::~DamageVignette()
{
	Finalize();
}


/// <summary>
/// ������
/// </summary>
void DamageVignette::Initialize()
{
	//�f�o�C�X�̎擾
	auto device  = m_commonResources->GetDeviceResources()->GetD3DDevice();
	//�R���e�L�X�g�̎擾
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	//	�R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/DamageVignetteVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/DamageVignetteGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/DamageVignettePS.cso");



	//	�C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	//	���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vs.ReleaseAndGetAddressOf())))
	{//	�G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	//	�W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_gs.ReleaseAndGetAddressOf())))
	{//	�G���[
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}

	//	�s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_ps.ReleaseAndGetAddressOf())))
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
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);

	//	�v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(context);




}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void DamageVignette::Update(const float& elapsedTime)
{
	//�I�u�W�F�N�g���L����
	if (!m_isActive)
	{
		return;
	}

	//�����x�̍X�V
	m_alpha -= elapsedTime * 1.0f;

	//�����ɂȂ�����
	if (m_alpha <= 0)
	{
		m_isActive = false;
	}

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void DamageVignette::Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(proj);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	if (!m_isActive)
	{
		return;
	}
	//�R���e�L�X�g�̎擾
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	//�f�o�C�X�̎擾
	auto states = m_commonResources->GetCommonStates();


	//	���_���(�|���S���̂S���_�̍��W���j
	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(Vector3(0.0f,  0.0f, 0.0f),Vector4::One,Vector2(0.0f, 0.0f)),
	};

	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.matView =  Matrix::Identity;
	cbuff.matProj =  Matrix::Identity;
	cbuff.matWorld = Matrix::Identity;
	cbuff.Diffuse =  Vector4(1, 1, 1, 1);
	cbuff.Time =     Vector4(m_alpha, 0.0f, 0.0f, 0.0f);

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//	�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//	�������`��w��
	ID3D11BlendState* blendstate = states->NonPremultiplied();

	//	�������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(states->DepthDefault(), 0);

	//	�J�����O�͍�����
	context->RSSetState(states->CullNone());

	//	�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vs.Get(), nullptr, 0);
	context->GSSetShader(m_gs.Get(), nullptr, 0);
	context->PSSetShader(m_ps.Get(), nullptr, 0);



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

void DamageVignette::SetIsActive(bool isActive)
{
	 m_isActive = isActive; 
	 //�����x�̏�����
	 m_alpha = 1;
}

/// <summary>
/// �G�t�F�N�g�̍쐬
/// </summary>
/// <param name="datas">�f�[�^</param>
void DamageVignette::Create(void* datas)
{
	UNREFERENCED_PARAMETER(datas);

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void DamageVignette::Finalize()
{
	// do nothing.
}


