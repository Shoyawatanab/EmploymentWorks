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
#include "Game/Effect/Particle/ParticleUtility.h"
#include "Libraries/WataLib/GameResources.h"

#include <algorithm>
#include <random>
#include <cmath>

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// �C���v�b�g���C�A�E�g
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> ChargeEffect::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0,							 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
ChargeEffect::ChargeEffect(CommonResources* resources)
	:
	m_commonResources{ resources },
	m_timer{}
	, m_isActive{ false }
	, m_CBuffer{}
	, m_inputLayout{}
	, m_batch{}
	, m_states{}
	, m_texture{}
	, m_vertexShader{}
	, m_pixelShader{}
	, m_geometryShader{}
	, m_world{}
	, m_view{}
	, m_proj{}
	, m_billboard{}
	, m_vertices{}
	, m_cameraPosition{}
	, m_cameraTarget{}
	, m_ChargeEffectUtility{}
	, m_position{}
	, m_scale{}
	,m_time{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ChargeEffect::~ChargeEffect()
{
}

/// <summary>
/// ������
/// </summary>
void ChargeEffect::Initialize()
{

	ID3D11Device1* device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	ID3D11DeviceContext1* context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	//	�V�F�[�_�[�̍쐬
	CreateShader();

	//	�摜�̓ǂݍ��݁i�Q���Ƃ��f�t�H���g�͓ǂݍ��ݎ��s��nullptr)
	//LoadTexture(L"Resources/Textures/da.png");

	m_texture.push_back(m_commonResources->GetGameResources()->GetTexture("da"));

	//	�v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);

	m_states = std::make_unique<CommonStates>(device);



}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime"></param>
void ChargeEffect::Update(const float& elapsedTime)
{
	if (!m_isActive)
	{
		return;
	}

	for (auto it = m_ChargeEffectUtility.begin(); it != m_ChargeEffectUtility.end(); )
	{
		if (!it->Update(elapsedTime)) {
			it = m_ChargeEffectUtility.erase(it);  // �폜��̐V�����C�e���[�^�[���擾
		}
		else {
			++it;  // �폜���Ȃ������ꍇ�͎��̗v�f��
		}
	}


	if (fmod(m_time, 0.5f) < elapsedTime)
	{
		CreateUtikity();

	}


	if (m_time >= 1.5f)
	{
		m_time = 0.0f;
		m_isActive = false;
	}

	m_time += elapsedTime;


}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void ChargeEffect::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	if (!m_isActive)
	{
		return;
	}

	ID3D11DeviceContext1* context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	//	���_���(�|���S���̂S���_�̍��W���j


	//	�o�^����Ă��钸�_�����Z�b�g
	m_vertices.clear();
	for (ParticleUtility& li : m_ChargeEffectUtility)
	{
		VertexPositionColorTexture vPCT;
		//	�\������p�[�e�B�N���̒��S���W�݂̂�����B
		//	���܂�AC++�ŗp�ӂ��Ă���f�[�^�����ł̓e�N�X�`����\���ł��Ȃ��B
		//	�@���W�I���g���V�F�[�_���g�����O��̃f�[�^�A�Ƃ�������
		vPCT.position = XMFLOAT3(li.GetPosition());
		//	�e�N�X�`���̐F
		vPCT.color = XMFLOAT4(li.GetNowColor());
		//	���݂̃e�N�X�`���̃X�P�[�����uXMFLOAT2�v��X�ɓ����B
		//	Y�͎g���Ă��Ȃ����A����������Texture��UV���W�Ƃ͈Ⴄ�g�����ɂȂ��Ă��邱�Ƃɒ���
		vPCT.textureCoordinate = XMFLOAT2(li.GetNowScale().x, 0.0f);

		m_vertices.push_back(vPCT);
	}

	//	�\������_���Ȃ��ꍇ�͕`����I���
	if (m_vertices.empty())
	{
		m_isActive = false;
		return;
	}


	// �r���{�[�h�}�g���b�N�X���v�Z����
	m_billboard = view.Invert();
	m_billboard._41 = 0.0f;
	m_billboard._42 = 0.0f;
	m_billboard._43 = 0.0f;

	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = m_billboard.Transpose();
	cbuff.Diffuse = SimpleMath::Vector4(1, 1, 1, 1);

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

	//	�������`��w��		��ԃA���t�@����
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	//	�������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthRead(), 0);

	//	�J�����O�͂Ȃ�
	context->RSSetState(m_states->CullNone());

	//	�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	for (int i = 0; i < m_texture.size(); i++)
	{
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	//	�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	//	�w�肵�����W�𒆐S�ɁA�V�F�[�_���Ŕ|���S���𐶐��E�`�悳����
	m_batch->Begin();

	//	�����܂ł̏����̊֌W��A�ȉ��͎g���Ȃ�
	//m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);

	//	�W�I���g���V�F�[�_��Point���󂯎�邱�ƂɂȂ��Ă��邽�߁A
	//	�����ł�D3D11_PRIMITIVE_TOPOLOGY_POINTLIST���g��
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());

	m_batch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);


}

void ChargeEffect::SetIsActive(bool isActive)
{
	m_isActive = isActive;

}

void ChargeEffect::Create(void* datas)
{

	CreateChargeEffectDatas* data = static_cast<CreateChargeEffectDatas*>(datas);

	m_position = data->Position;

	CreateUtikity();

	m_time = 0.0f;

}

/// <summary>
/// �e�N�X�`�����\�[�X�ǂݍ��݊֐�
/// </summary>
/// <param name="path">���΃p�X(Resources/Textures/�E�E�E.png�Ȃǁj</param>
void ChargeEffect::LoadTexture(const wchar_t* path)
{

	ID3D11Device1* device = m_commonResources->GetDeviceResources()->GetD3DDevice();


	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	DirectX::CreateWICTextureFromFile(device, path, nullptr, texture.ReleaseAndGetAddressOf());

	m_texture.push_back(texture);
}



/// <summary>
/// Shader�쐬�����������������֐�
/// </summary>
void ChargeEffect::CreateShader()
{
	ID3D11Device1* device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	//	�R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");

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

void ChargeEffect::CreateUtikity()
{

	int count = 12;
	float radius = 2.0f;
	Vector3 scale = Vector3(2, 2, 2);


	for (int i = 0; i < count; i++)
	{
		//�p�x�����߂�
		float angle = DirectX::XM_2PI * i / count;
		float x = radius * cos(angle);
		float z = radius * sin(angle);

		Vector3 pos = Vector3(x, 0.0f, z);

		Vector3 velocity = Vector3(cos(angle), 0.0f, sin(angle));

		//	0�`2PI�̒l��default_random_engine(���炭���΂炭��mt19937)���g���Ď��o��
		ParticleUtility pU(
			3.0f,																			//	��������(s)
			pos + m_position,				                                                        //	����W
			velocity,		//	���x
			SimpleMath::Vector3(0.5f,0.0f,0.5f),														//	�����x
			scale,                                                      //	�����X�P�[��
			scale,							                  //	�ŏI�X�P�[��
			SimpleMath::Color(1.f, 1.f, 1.f, 1.f),											// �����J���[�A
			SimpleMath::Color(1.f, 1.f, 1.f, -1.f)										   //	�ŏI�J���[
		);

		m_ChargeEffectUtility.push_back(pU);
	}




}


