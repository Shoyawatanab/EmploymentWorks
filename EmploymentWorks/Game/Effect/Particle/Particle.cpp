//--------------------------------------------------------------------------------------
// File: Particle.cpp
//
// �p�[�e�B�N���N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Particle.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Libraries/MyLib/BinaryFile.h"
#include "DeviceResources.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>
#include <algorithm>
#include <random>

#include "Game/Effect/Particle/ParticleUtility.h"
#include "Game/Observer/EventParams.h"
#include "Libraries/WataLib/GameResources.h"


/// <summary>
/// �C���v�b�g���C�A�E�g
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> Particle::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,    0,   0,                                                                           D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(DirectX::SimpleMath::Vector3),                                        D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	   0,   sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
Particle::Particle(CommonResources* resources)
	:
	m_commonResources{resources}
	, m_isActive{ false }
	,m_CBuffer{}
	,m_inputLayout{}
	,m_batch{}
	,m_states{}
	,m_texture{}
	,m_texture2{}
	,m_vertexShader{}
	,m_pixelShader{}
	,m_geometryShader{}
	,m_billboard{}
	,m_vertices{}
	,m_particleUtility{}
	,m_position{}
	,m_scale{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Particle::~Particle()
{
}

/// <summary>
/// ������
/// </summary>
void Particle::Initialize()
{
	using namespace DirectX;

	//�f�o�C�X�̎擾
	ID3D11Device1* device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	//�R���e�L�X�g�̎擾
	ID3D11DeviceContext1* context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	//	�V�F�[�_�[�̍쐬
	CreateShader();
	//�摜�̎擾
	m_texture.push_back(m_commonResources->GetGameResources()->GetTexture("da"));

	//	�v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);
	//�R�����X�e�[�g�̍쐬
	m_states = std::make_unique<CommonStates>(device);


}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime"></param>
void Particle::Update(const float& elapsedTime)
{
	//�I�u�W�F�N�g���L����
	if (!m_isActive)
	{
		return;
	}

	//���[�e�B���e�B�̍X�V
	for (auto it = m_particleUtility.begin(); it != m_particleUtility.end(); )
	{
		if (!it->Update(elapsedTime)) {
			it = m_particleUtility.erase(it);  // �폜��̐V�����C�e���[�^�[���擾
		}
		else {
			++it;  // �폜���Ȃ������ꍇ�͎��̗v�f��
		}
	}


}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void Particle::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	using namespace DirectX;

	//�I�u�W�F�N�g���L����
	if (!m_isActive)
	{
		return;
	}

	ID3D11DeviceContext1* context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	//	���_���(�|���S���̂S���_�̍��W���j


	//	�o�^����Ă��钸�_�����Z�b�g
	m_vertices.clear();
	for (ParticleUtility& li : m_particleUtility)
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
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

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


	//	�W�I���g���V�F�[�_��Point���󂯎�邱�ƂɂȂ��Ă��邽�߁A
	//	�����ł�D3D11_PRIMITIVE_TOPOLOGY_POINTLIST���g��
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());

	m_batch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);


}

void Particle::SetIsActive(bool isActive)
{
	m_isActive = isActive;
	
}

/// <summary>
/// �G�t�F�N�g�̍쐬
/// </summary>
/// <param name="datas">�f�[�^</param>
void Particle::Create(void* datas)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//�f�[�^�̎擾
	Vector3* pos = static_cast<DirectX::SimpleMath::Vector3*>(datas);

	//�p�[�e�B�N�����쐬
	for (int i = 0; i < UTILITY_COUNT; i++)
	{

		//	���S�ȃ����_�����n�[�h�E�F�A�I�ɐ������邽�߂̃N���X�̕ϐ�
		std::random_device seed;
		//�����_���G���W��
		std::default_random_engine engine(seed());
		//�����_���͈͂̎w��
		std::uniform_real_distribution<> dist(0, XM_2PI);
		//�p�x�̍쐬
		float angle = static_cast<float>(dist(engine));
		//�����_���͈͂̎w��
		std::uniform_real_distribution<> dist2(0.5f, 1.0f);
		//�����̐���
		float speedY = static_cast<float>(dist2(engine) / 2.5f);
		float speedX = static_cast<float>(dist2(engine));

		//���S������ˏ�ɍL��������̃x�N�g��
		Vector3 vectorFormCenter = Vector3(
			GENERATE_RADIUS * cosf(angle),
			0.0f,
			GENERATE_RADIUS * sinf(angle)
		);
		//���S����̋������擾
		float distanceFormCenter = vectorFormCenter.Length();
		//���K��
		vectorFormCenter.Normalize();
		//���S����̋����ɉ����đ��x�𑝉�
		float scaleFactor = 2.0f + (distanceFormCenter / GENERATE_RADIUS);
		Vector3 adjustedVelocity = vectorFormCenter * scaleFactor;

		//���ɂȂ�悤�ɔ��]
		Vector3 velocity = -adjustedVelocity;
		//�������W
		Vector3 dustPos = *pos + Vector3(
			GENERATE_RADIUS * cosf(angle),
			0.0f,
			GENERATE_RADIUS * sinf(angle)

		);


		//	0�`2PI�̒l��default_random_engine(���炭���΂炭��mt19937)���g���Ď��o��
		ParticleUtility pU(
			1.0f,																			//	��������(s)
			dustPos,																		//	����W
			Vector3(-velocity.x * speedX, speedY, -velocity.z * speedX),					//	���x
			Vector3::Zero,																	//	�����x
			Vector3::One,																	//	�����X�P�[���A
			Vector3(10, 10, 10),															//  �ŏI�X�P�[��
			Color(1.f, 1.f, 1.f, 1.f),														//	�����J���[
			Color(1.f, 1.f, 1.f, -1.f)														//  �ŏI�J���[
		);
		//�ǉ�
		m_particleUtility.push_back(pU);
	}


}


/// <summary>
/// Shader�쐬�����������������֐�
/// </summary>
void Particle::CreateShader()
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

/// <summary>
/// �r���{�[�h�쐬�֐�
/// </summary>
/// <param name="target">�J�����^�[�Q�b�g�i�����_�j</param>
/// <param name="eye">�J�����A�C�i�J�������W�j</param>
/// <param name="up">������x�N�g���i��{��Y�݂̂P�̃x�N�g���j</param>
void Particle::CreateBillboard(DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up)
{
	using namespace DirectX::SimpleMath;

	m_billboard = Matrix::CreateBillboard(Vector3::Zero,eye - target, up);

	Matrix rot = Matrix::Identity;
	rot._11 = -1;
	rot._33 = -1;

	m_billboard = rot * m_billboard;
}

