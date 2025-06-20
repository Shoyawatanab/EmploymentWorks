//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2025/06/16
// <file>			SpriteInstancing.cpp
// <�T�v>		�@�@�X�v���C�g�ł̃C���X�^���V���O
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"SpriteInstancing.h"

/// <summary>
/// �X�v���C�g�C���X�^���V���O�p���̓��C�A�E�g
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> SPRITE_INSTANCE_INPUT_LAYOUT =
{
	// �x�[�X���_�i�|�C���g�j
	{ "POSITION",			0, DXGI_FORMAT_R32G32B32_FLOAT		, 0, 0	, D3D11_INPUT_PER_VERTEX_DATA	, 0 },
	{ "TEXCOORD",			0, DXGI_FORMAT_R32G32_FLOAT			, 0, 12	, D3D11_INPUT_PER_VERTEX_DATA	, 0 },
	// �C���X�^���X�f�[�^
	{ "INSTANCEPOS",		0, DXGI_FORMAT_R32G32B32_FLOAT		, 1, 0	, D3D11_INPUT_PER_INSTANCE_DATA	, 1 },
	{ "INSTANCESIZE",		0, DXGI_FORMAT_R32G32B32_FLOAT		, 1, 12	, D3D11_INPUT_PER_INSTANCE_DATA	, 1 },
	{ "INSTANCECOLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT	, 1, 24	, D3D11_INPUT_PER_INSTANCE_DATA	, 1 },
	{ "INSTANCETEXCOORD",	0, DXGI_FORMAT_R32G32B32A32_FLOAT	, 1, 40	, D3D11_INPUT_PER_INSTANCE_DATA	, 1 },
	{ "INSTANCEROT" ,		0, DXGI_FORMAT_R32G32B32A32_FLOAT	, 1, 56 , D3D11_INPUT_PER_INSTANCE_DATA , 1	}
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
SpriteInstancing::SpriteInstancing()
{
	m_maxInstance = 0;
	m_onBillboard = true;
}

/// <summary>
/// ����������
/// </summary>
void SpriteInstancing::Initialize(ID3D11Device* device, int maxInstance)
{
	// �C���X�^���X�̗ʌ���
	m_maxInstance = std::min(maxInstance, MAX_INSTANCE);
	// �V�F�[�_�̍쐬
	m_shaderSet.vertexShader = ShaderManager2::CreateVSShader(device, "SpriteVS.cso");
	m_shaderSet.pixelShader = ShaderManager2::CreatePSShader(device, "SpritePS.cso");
	m_shaderSet.inputLayout = ShaderManager2::CreateInputLayout(device, SPRITE_INSTANCE_INPUT_LAYOUT, "SpriteVS.cso");
	// �萔�o�b�t�@�쐬
	m_constantBuffer = ShaderManager2::CreateConstantBuffer<SpriteConstantBuffer>(device);



	// �o�b�t�@�쐬
	CreateVertexBuffer(device);
	CreateInstanceBuffer(device);
}

/// <summary>
/// �`�揈��
/// </summary>
void SpriteInstancing::Render(ID3D11DeviceContext* context,
	DirectX::DX11::CommonStates* states,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection,
	std::vector<SpriteInstanceData>& instances)
{
	if (instances.empty()) { return; }
	if (instances.size() > static_cast<size_t>(m_maxInstance)) { return; }

	// ���ۂɕ`�悷��C���X�^���X��
	int instanceCount = static_cast<int>(std::min(instances.size(), static_cast<size_t>(m_maxInstance)));
	// �C���X�^���X�o�b�t�@�X�V
	D3D11_MAPPED_SUBRESOURCE mappedResources;
	if (SUCCEEDED(context->Map(m_instanceBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResources)))
	{
		memcpy(mappedResources.pData, instances.data(), sizeof(SpriteInstanceData) * instanceCount);
		context->Unmap(m_instanceBuffer.Get(), 0);
	}
	// �J�����̉E�A��x�N�g���v�Z
	DirectX::SimpleMath::Vector3 cameraRight, cameraUp;
	CalculateCameraVectors(view, cameraRight, cameraUp);

	// �萔�o�b�t�@�X�V
	SpriteConstantBuffer cb;
	cb.view = view.Transpose();
	cb.projection = projection.Transpose();
	cb.CameraRight = DirectX::SimpleMath::Vector4(cameraRight.x, cameraRight.y, cameraRight.z, 0.0f);
	cb.CameraUp = DirectX::SimpleMath::Vector4(cameraUp.x, cameraUp.y, cameraUp.z, 0.0f);
	cb.color = DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	cb.onBillboard = m_onBillboard;

	context->UpdateSubresource(m_constantBuffer.Get(), 0, nullptr, &cb, 0, 0);

	// �����_�����O�X�e�[�g�ݒ�
	ID3D11Buffer* pBuffers[2] = { m_vertexBuffer.Get(), m_instanceBuffer.Get() };
	UINT strides[2] = { sizeof(BaseVertex), sizeof(SpriteInstanceData) };
	UINT offsets[2] = { 0, 0 };
	context->IASetVertexBuffers(0, 2, pBuffers, strides, offsets);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetInputLayout(m_shaderSet.inputLayout.Get());

	// �V�F�[�_�[�ݒ�
	context->VSSetShader(m_shaderSet.vertexShader.Get(), nullptr, 0);
	context->PSSetShader(m_shaderSet.pixelShader.Get(), nullptr, 0);

	// �萔�o�b�t�@�ݒ�
	ID3D11Buffer* pConstantBuffer = m_constantBuffer.Get();
	context->VSSetConstantBuffers(0, 1, &pConstantBuffer);
	context->GSSetConstantBuffers(0, 1, &pConstantBuffer);
	context->PSSetConstantBuffers(0, 1, &pConstantBuffer);

	// �e�N�X�`���ƃT���v���[�ݒ�
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());
	ID3D11SamplerState* pSampler = states->LinearWrap();
	context->PSSetSamplers(0, 1, &pSampler);

	// �u�����h�X�e�[�g�i�A���t�@�u�����h�j
	context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xffffffff);
	// �f�v�X�X�e���V���X�e�[�g
	context->OMSetDepthStencilState(states->DepthDefault(), 0);
	// ���X�^���C�U�[�X�e�[�g
	context->RSSetState(states->CullNone());

	// �`��i6�̒��_�Ŏl�p�`���쐬�j
	context->DrawInstanced(6, instanceCount, 0, 0);
}

/// <summary>
/// ���_�V�F�[�_�쐬
/// </summary>
/// <param name="device"></param>
void SpriteInstancing::CreateVertexBuffer(ID3D11Device* device)
{
	using namespace DirectX::SimpleMath;

	// �l�p�`�̒��_�f�[�^�i6�̒��_�ŎO�p�`��2�j
	BaseVertex vertices[6] = {
		// �O�p�`1�i�����A�E���A����j
		{ Vector3(-0.5f, -0.5f, 0.0f), Vector2(0.0f, 1.0f) },
		{ Vector3(0.5f, -0.5f, 0.0f), Vector2(1.0f, 1.0f) },
		{ Vector3(-0.5f, 0.5f, 0.0f), Vector2(0.0f, 0.0f) },
		// �O�p�`2�i����A�E���A�E��j
		{ Vector3(-0.5f, 0.5f, 0.0f), Vector2(0.0f, 0.0f) },
		{ Vector3(0.5f, -0.5f, 0.0f), Vector2(1.0f, 1.0f) },
		{ Vector3(0.5f, 0.5f, 0.0f), Vector2(1.0f, 0.0f) }
	};

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDesc.ByteWidth = sizeof(vertices);
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;

	device->CreateBuffer(&bufferDesc, &initData, &m_vertexBuffer);
}

/// <summary>
/// �萔�o�b�t�@�̍쐬
/// </summary>
void SpriteInstancing::CreateInstanceBuffer(ID3D11Device* device)
{
	// ���I�C���X�^���X�o�b�t�@�쐬
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(SpriteInstanceData) * m_maxInstance;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	device->CreateBuffer(&bufferDesc, nullptr, &m_instanceBuffer);
}

/// <summary>
/// �J�����x�N�g���̌v�Z
/// </summary>
void SpriteInstancing::CalculateCameraVectors(const DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Vector3& right, DirectX::SimpleMath::Vector3& up)
{
	// �r���[�s�񂩂�A�J�����̉E�A��x�N�g���𒊏o
	right = DirectX::SimpleMath::Vector3(view._11, view._21, view._31);
	up = DirectX::SimpleMath::Vector3(view._12, view._22, view._32);

	right.Normalize();
	up.Normalize();
}