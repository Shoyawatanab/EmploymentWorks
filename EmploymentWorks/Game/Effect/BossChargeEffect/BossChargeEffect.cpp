#include "pch.h"
#include "BossChargeEffect.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Camera/Camera.h"
#include "GameBase/GameResources.h"
#include "GameBase/Component/Components.h"
#include "Game/Effect/ParticleUtility.h"
#include "GameBase/Shader/ShaderFactory.h"



/// <summary>
/// �C���v�b�g���C�A�E�g
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> BossChargeEffect::INPUT_LAYOUT =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                                                                           D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(DirectX::SimpleMath::Vector3),                                        D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,	     0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};



/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
BossChargeEffect::BossChargeEffect(Scene* scene)
	:
	Actor(scene)
	,m_inputLayout{}
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	AddComponent<EffectComponent>(this, std::bind(&BossChargeEffect::Render, this, std::placeholders::_1));



	using namespace DirectX;

	//�f�o�C�X�̎擾
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	//�R���e�L�X�g�̎擾
	ID3D11DeviceContext1* context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//	�V�F�[�_�[�̍쐬
	CreateShader();

	//�摜�̎擾
	m_texture.push_back(GameResources::GetInstance()->GetTexture("da"));

	//	�v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);
	//�R�����X�e�[�g�̍쐬
	m_states = std::make_unique<CommonStates>(device);

	SetActive(false);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossChargeEffect::~BossChargeEffect()
{
}

/// <summary>
/// �ʃA�b�v�f�[�g
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void BossChargeEffect::UpdateActor(const float& deltaTime)
{

	//���[�e�B���e�B�̍X�V
	for (auto it = m_ChargeEffectUtility.begin(); it != m_ChargeEffectUtility.end(); )
	{
		if (!it->Update(deltaTime)) {
			it = m_ChargeEffectUtility.erase(it);  // �폜��̐V�����C�e���[�^�[���擾
		}
		else {
			++it;  // �폜���Ȃ������ꍇ�͎��̗v�f��
		}
	}

	//0.5�b���ƂɃG�t�F�N�g�̍쐬
	if (fmod(m_time, GENERATION_INTERVAL) < deltaTime)
	{
		CreateUtility();
	}

	//�I�����ǂ���
	if (m_time >= GENERATION_TIME)
	{
		//������
		m_time = 0.0f;
		SetActive(false);
	}

	//�o�ߎ��Ԃ̉��Z
	m_time += deltaTime;

}



/// <summary>
/// �`��
/// </summary>
/// <param name="camera">�J����</param>
void BossChargeEffect::Render(const Camera& camera)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//�R���e�L�X�g�̎擾
	ID3D11DeviceContext1* context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	auto view = camera.GetViewMatrix();
	auto projection = camera.GetProjectionMatrix();

	//	�o�^����Ă��钸�_�����Z�b�g
	m_vertices.clear();
	for (ParticleUtility& li : m_ChargeEffectUtility)
	{
		VertexPositionColorTexture vPCT;
		vPCT.position = XMFLOAT3(li.GetPosition());
		//	�e�N�X�`���̐F
		vPCT.color = XMFLOAT4(li.GetNowColor());
		//	���݂̃e�N�X�`���̃X�P�[�����uXMFLOAT2�v��X�ɓ����B
		vPCT.textureCoordinate = XMFLOAT2(li.GetNowScale().x, 0.0f);

		m_vertices.push_back(vPCT);
	}

	//	�\������_���Ȃ��ꍇ�͕`����I���
	if (m_vertices.empty())
	{
		return;
	}


	// �r���{�[�h�}�g���b�N�X���v�Z����
	m_billboard = view.Invert();
	m_billboard._41 = 0.0f;
	m_billboard._42 = 0.0f;
	m_billboard._43 = 0.0f;

	//�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = projection.Transpose();
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

	m_batch->Begin();

	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());

	m_batch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);


}

/// <summary>
/// �A�N�e�B�u��ԂɂȂ�����
/// </summary>
void BossChargeEffect::OnEnable()
{
	m_time = 0.0f;
}

void BossChargeEffect::CreateShader()
{
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	auto shaderFactory = ShaderFactory::GetInstance();

	//�e�V�F�[�_�[�̍쐬
	m_vertexShader = shaderFactory->CreateVS(device, "ParticleVS.cso");
	m_pixelShader = shaderFactory->CreatePS(device, "ParticlePS.cso");
	m_geometryShader = shaderFactory->CreateGS(device, "ParticleGS.cso");

	m_inputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "ParticleVS.cso");


	//	�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);

}

void BossChargeEffect::CreateUtility()
{

	using namespace DirectX::SimpleMath;

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

		ParticleUtility pU(
			3.0f,																			//	��������(s)
			pos + GetTransform()->GetWorldPosition(),				                                                        //	����W
			velocity,		//	���x
			Vector3(0.5f, 0.0f, 0.5f),														//	�����x
			scale,                                                      //	�����X�P�[��
			scale,							                  //	�ŏI�X�P�[��
			Color(1.f, 1.f, 1.f, 1.f),											// �����J���[�A
			Color(1.f, 1.f, 1.f, -1.f)										   //	�ŏI�J���[
		);

		m_ChargeEffectUtility.push_back(pU);
	}

}
