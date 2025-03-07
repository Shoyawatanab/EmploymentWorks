#include "pch.h"
#include "CircleParticle.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/BinaryFile.h"



using namespace DirectX;
using namespace DirectX::SimpleMath;

//�C���v�b�g���C�A�E�g
const std::vector<D3D11_INPUT_ELEMENT_DESC> CircleParticle::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0,							 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

float Lerp(const float& start, const float& end, const float& t)
{
	return (1.0f - t) * start + t * end;
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resourece">���ʃ��\�[�X</param>
CircleParticle::CircleParticle(CommonResources* resourece)
	:
	m_commonResources{resourece}
	,m_Batch{}
	,m_time{}
	,m_inputLayout{}
	,m_scale{}
	,m_position{}
	,m_alpha{}
	,m_vertexShader{}
	,m_pixelShader{}
	,m_CBuffer{}
	,m_world{}

{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CircleParticle::~CircleParticle()
{

}

/// <summary>
/// ������
/// </summary>
void CircleParticle::Initialize()
{


	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	//�V�F�[�_�[�t�@�C���̓ǂݍ���
	BinaryFile VS = BinaryFile::LoadFile(L"Resources/Shaders/CircleParticleVS.cso");
	BinaryFile PS = BinaryFile::LoadFile(L"Resources/Shaders/CircleParticlePS.cso");

	//	�C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VS.GetData(), VS.GetSize(),
		m_inputLayout.ReleaseAndGetAddressOf());

	//���_�V�F�[�_�[���쐬���i�[
	DX::ThrowIfFailed(
		device->CreateVertexShader(
			VS.GetData(),
			VS.GetSize(),
			nullptr,
			m_vertexShader.ReleaseAndGetAddressOf())
	);

	//�s�N�Z���V�F�[�_�[���쐬���i�[
	DX::ThrowIfFailed(
		device->CreatePixelShader(
			PS.GetData(),
			PS.GetSize(),
			nullptr,
			m_pixelShader.ReleaseAndGetAddressOf())
	);

	//	�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);


	//�v���~�e�B�u�o�b�`�̍쐬
	m_Batch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	//�����x�̏�����
	m_alpha = 1.0f;
	//�o�ߎ��Ԃ̏�����
	m_time = 0;
	//X�������Ɋ�Â��ĕύX
	m_scale = DirectX::SimpleMath::Vector3::One;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>ture �I��  false�@�p���@</returns>
bool CircleParticle::Update(float elapsedTime)
{

	//�o�ߎ��Ԃ̉��Z
	m_time += elapsedTime;

	//�I��������
	if (m_time >= 2)
	{
		return true;
	}

	return false ; 

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void CircleParticle::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	//���_�f�[�^
	VertexPositionTexture circleVertex[4] = {
		VertexPositionTexture(SimpleMath::Vector3(-0.5f,-0.5f ,0.0f), SimpleMath::Vector2(0.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.5f ,-0.5f ,0.0f), SimpleMath::Vector2(1.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.5f,0.5f  ,0.0f ), SimpleMath::Vector2(1.0f, 1.0f)),
		VertexPositionTexture(SimpleMath::Vector3(-0.5f,0.5f ,0.0f ), SimpleMath::Vector2(0.0f, 1.0f)),
	};

	//���[���h�̌v�Z
	m_world = Matrix::CreateScale(m_scale);
	//�r���{�[�h����
	m_world *= view.Invert();
	m_world._41 = 0.0f;
	m_world._42 = 0.0f;
	m_world._43 = 0.0f;
	m_world *= Matrix::CreateTranslation(m_position);

	//�o�b�t�@�̍쐬
	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = m_world.Transpose();
	cbuff.diffuse = Vector4(1, 1, 1, m_alpha);
	cbuff.time = Vector4(m_time, 1, 1, 1);

	//�o�b�t�@�̍X�V
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//�e�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//	�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//�u�����h�̐ݒ�
	context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

	//	�[�x�o�b�t�@�ɏ������ݎQ��
	context->OMSetDepthStencilState(states->DepthDefault(), 0);

	//	�J�����O��Ԃ̐ݒ�
	context->RSSetState(states->CullNone());

	//�V�F�[�_�[�̃Z�b�g
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
	//�s�N�Z���V�F�[�_�[�ɉ摜��o�^
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());
	//�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());
	//�|���S���̕`��
	m_Batch->Begin();
	m_Batch->DrawQuad(circleVertex[0], circleVertex[1], circleVertex[2], circleVertex[3]);
	m_Batch->End();

	//�V�F�[�_�[�̉���
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

// �I������
void CircleParticle::Finalize()
{
}


