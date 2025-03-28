/*
	@file	ChargeEffect.cpp
	@brief	��ʓI�ȃV�[���N���X
*/
#include "pch.h"
#include "ChargeEffect.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Observer/EventParams.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

///	<summary>
///	�C���v�b�g���C�A�E�g
///	</summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> ChargeEffect::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
ChargeEffect::ChargeEffect(CommonResources* resources)
	:
	m_commonResources{resources},
	m_position{},
	m_scale{}
	,m_isActive{false}
	, m_time{}
	,m_damageCount{}
	,m_CBuffer{}
	,m_inputLayout{}
	,m_batch{}
	,m_vs{}
	,m_ps{}
	,m_gs{}
	,m_world{}
	,m_view{}
	,m_proj{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ChargeEffect::~ChargeEffect()
{
	Finalize();
}


/// <summary>
/// ������
/// </summary>
void ChargeEffect::Initialize()
{

	auto device  = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states  = m_commonResources->GetCommonStates();



	//	�R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ChargeEffectVS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ChargeEffectPS.cso");



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
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(context);




}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void ChargeEffect::Update(const float& elapsedTime)
{
	if (!m_isActive)
	{
		return;
	}


		//�o�ߎ��Ԃ̉��Z
	m_time += elapsedTime;

	//�I��������
	if (m_time >= 2)
	{
		//m_isActive = false;
	}



}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void ChargeEffect::Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj)
{

	if (!m_isActive)
	{
		return;
	}

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	//���_�f�[�^
	//VertexPositionTexture vertex[4] = {
	//	VertexPositionTexture(SimpleMath::Vector3(-0.5f,-0.5f ,0.0f), SimpleMath::Vector2(0.0f, 0.0f)),
	//	VertexPositionTexture(SimpleMath::Vector3(0.5f ,-0.5f ,0.0f), SimpleMath::Vector2(1.0f, 0.0f)),
	//	VertexPositionTexture(SimpleMath::Vector3(0.5f,0.5f  ,0.0f), SimpleMath::Vector2(1.0f, 1.0f)),
	//	VertexPositionTexture(SimpleMath::Vector3(-0.5f,0.5f ,0.0f), SimpleMath::Vector2(0.0f, 1.0f)),
	//};

	VertexPositionTexture vertex[4] = {
	VertexPositionTexture(SimpleMath::Vector3(-0.5f,-0.0f ,-0.5f), SimpleMath::Vector2(0.0f, 0.0f)),
	VertexPositionTexture(SimpleMath::Vector3(0.5f ,-0.0f ,-0.5f), SimpleMath::Vector2(1.0f, 0.0f)),
	VertexPositionTexture(SimpleMath::Vector3(0.5f,0.0f  ,0.5f), SimpleMath::Vector2(1.0f, 1.0f)),
	VertexPositionTexture(SimpleMath::Vector3(-0.5f,0.0f ,0.5f), SimpleMath::Vector2(0.0f, 1.0f)),
	};


	Vector3 pos = m_position;
	pos.y = 1.0f;

	Matrix matrix = Matrix::CreateScale(m_scale);
	matrix *= Matrix::CreateTranslation(pos);




	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = matrix.Transpose();
	cbuff.Diffuse = SimpleMath::Vector4(1, 1, 1, 1);
	cbuff.Time = SimpleMath::Vector4(m_time, 0.0f, 0.0f, 0.0f);

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
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
	context->PSSetShader(m_ps.Get(), nullptr, 0);



	//	�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	//	�|���S����`��
	m_batch->Begin();
	m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_batch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);






}

void ChargeEffect::SetIsActive(bool isActive)
{
	 m_isActive = isActive; 

	 m_time = 0;
}

void ChargeEffect::Create(void* datas)
{

	EventParams::CreateChargeEffectDatas* data = static_cast<EventParams::CreateChargeEffectDatas*>(datas);

	DirectX::SimpleMath::Vector3 pos = data->Position;
	DirectX::SimpleMath::Vector3 scale = data->Scale;

	m_position = pos;

	m_scale = scale;

	m_position = Vector3::Zero;


}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void ChargeEffect::Finalize()
{
	// do nothing.
}


