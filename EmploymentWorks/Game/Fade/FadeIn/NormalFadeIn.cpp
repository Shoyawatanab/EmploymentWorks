#include "pch.h"
#include "NormalFadeIn.h"
#include "GameBase/Shader/ShaderFactory.h"
#include "GameBase/Common/Commons.h"

///	<summary>
///	�C���v�b�g���C�A�E�g
///	</summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> NormalFadeIn::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// �R���X�g���N
/// </summary>
NormalFadeIn::NormalFadeIn()
	:
	m_batch{}
	,m_time{}
{
	//�V�F�[�_�[�̍쐬
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	CreateShader(device,context);

	//	�v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(context);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
NormalFadeIn::~NormalFadeIn()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
/// <returns>true�F�I���@false�F���s��</returns>
bool NormalFadeIn::Update(const float& deltaTime)
{

	//���Ԃ̉��Z
	m_time += deltaTime;

	return m_time >= MAX_TIME;
}

/// <summary>
/// �`��
/// </summary>
void NormalFadeIn::Render()
{

	//�V�F�[�_�[�̍쐬
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = CommonResources::GetInstance()->GetCommonStates();

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
	cbuff.time = DirectX::SimpleMath::Vector4(m_time, MAX_TIME, 1, 1);

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
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
	
	//	�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	//	�|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_batch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

void NormalFadeIn::Enter()
{
	m_time = 0.0f;
}

void NormalFadeIn::Exit()
{

}



void NormalFadeIn::CreateShader(ID3D11Device1* device, ID3D11DeviceContext* context)
{

	auto shaderFactory = ShaderFactory::GetInstance();
	//�e�V�F�[�_�[�̍쐬
	m_vertexShader = shaderFactory->CreateVS(device, "FadeVS.cso");
	m_pixelShader = shaderFactory->CreatePS(device, "NormalFadeInPS.cso");
	m_geometryShader = shaderFactory->CreateGS(device, "FadeGS.cso");

	m_inputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "FadeVS.cso");

	//	�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);

}
