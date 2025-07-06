#include "pch.h"
#include "BoomerangFadeIn.h"
#include "GameBase/Shader/ShaderFactory.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/GameResources.h"
#include "Game/Fade/EasingFunctions.h"



///	<summary>
///	�C���v�b�g���C�A�E�g
///	</summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> BoomerangFadeIn::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// �R���X�g���N
/// </summary>
BoomerangFadeIn::BoomerangFadeIn()
	:
	m_batch{}
	,m_totalTime{}
{
	//�V�F�[�_�[�̍쐬
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	CreateShader();

	// �t�F�[�h�e�N�X�`���̎擾
	m_texture = GameResources::GetInstance()->GetTexture("fade");
	// �^�����e�N�X�`���̎擾
	m_stencilImage = GameResources::GetInstance()->GetTexture("mask");
	// �V�F�[�_�[�̐���
	CreateShader();
	// �v���~�e�B�u�o�b�`�̐���
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(context);
	// �R�����X�e�[�g�̐���
	m_states = std::make_unique<DirectX::CommonStates>(device);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangFadeIn::~BoomerangFadeIn()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
/// <returns>true�F�I���@false�F���s��</returns>
bool BoomerangFadeIn::Update(const float& deltaTime)
{

	m_totalTime -= deltaTime;

	// ���Ԃ��v�Z����( 0 �� 1 )
	m_totalTime = std::max(m_totalTime, 0.0f);


	return m_totalTime <= 0.0f;
}



/// <summary>
/// �`��
/// </summary>
void BoomerangFadeIn::Render()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DrawStencilImage();

	float easing = 0.0f;
	easing = std::max(0.0f, 1.0f - (m_totalTime / FADE_TIME));
	easing = std::max(0.0001f, Easing::easeInCubic(easing));

	ID3D11DeviceContext1* context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(SimpleMath::Vector3(0.0f, 0.0f, 0.0f),SimpleMath::Vector4::One, SimpleMath::Vector2(0.0f, 0.0f)),
	};

	// �V�F�[�_�[�ɓn�����̔}�̂��쐬����
	ConstBuffer cbuff;

	// �n���f�[�^��o�^����
	cbuff.matView = SimpleMath::Matrix::Identity;				// �X�N���[�����W�ŕ`�悷�邽�ߕs�v
	cbuff.matProj = SimpleMath::Matrix::Identity;				// �X�N���[�����W�ŕ`�悷�邽�ߕs�v
	cbuff.matWorld = SimpleMath::Matrix::Identity;				// �X�N���[�����W�ŕ`�悷�邽�ߕs�v
	cbuff.Diffuse = SimpleMath::Vector4::One;					// �e�N�X�`���̐F
	cbuff.time = SimpleMath::Vector4(easing, 0.0f, 0.0f, 0.0f);	// �t�F�[�h�̎��ԁi���v�f�̂ݎg�p�j


	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// �V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* ccb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, ccb);
	context->GSSetConstantBuffers(0, 1, ccb);
	context->PSSetConstantBuffers(0, 1, ccb);

	//	�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	//	�������`��w��
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();
	//	�������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);
	//	�J�����O�͐��ʂ̂ݍs��
	context->RSSetState(m_states->CullCounterClockwise());

	//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());
	// �}�X�N�摜���s�N�Z���V�F�[�_�ɓo�^����
	context->PSSetShaderResources(1, 1, m_captureSRV.GetAddressOf());

	//	�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	// �|���S���ŕ`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_batch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

void BoomerangFadeIn::Enter()
{
	m_totalTime = FADE_TIME;
}

void BoomerangFadeIn::Exit()
{

}



void BoomerangFadeIn::CreateShader()
{
	// �f�o�C�X�̎擾
	ID3D11Device* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

//�}�X�N�ȊO�̃V�F�[�_�[�̍쐬
	auto shaderFactory = ShaderFactory::GetInstance();
	//�e�V�F�[�_�[�̍쐬
	m_vertexShader = shaderFactory->CreateVS(device, "DieCuttingVS.cso");
	m_pixelShader = shaderFactory->CreatePS(device, "DieCuttingPS.cso");
	m_geometryShader = shaderFactory->CreateGS(device, "DieCuttingGS.cso");

	m_inputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "DieCuttingVS.cso");



//�}�X�N�p�̃V�F�[�_�[�̍쐬

		//�e�V�F�[�_�[�̍쐬
	m_maskVS = shaderFactory->CreateVS(device, "MaskVS.cso");
	m_maskPS = shaderFactory->CreatePS(device, "MaskPS.cso");
	m_maskGS = shaderFactory->CreateGS(device, "MaskGS.cso");

	m_maskInputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "MaskVS.cso");

	//	�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);


}

float BoomerangFadeIn::CalcrateFadeValue(float easing)
{
	return Easing::easeBetweenIn(easing, FADE_THRESHOLD, FADE_FIRST_SIZE, FADE_MAX_SIZE);;
}

void BoomerangFadeIn::DrawStencilImage()
{
	// �f�o�C�X���\�[�X�̎擾
	auto deviceResources = CommonResources::GetInstance()->GetDeviceResources();
	// �R���e�L�X�g�̎擾
	ID3D11DeviceContext* context = deviceResources->GetD3DDeviceContext();

	//	�`��ɂ��Ă̐ݒ���s��
	D3D11_TEXTURE2D_DESC texDesc;
	deviceResources->GetRenderTarget()->GetDesc(&texDesc);
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	deviceResources->GetD3DDevice()->CreateTexture2D(&texDesc, NULL, m_capture.ReleaseAndGetAddressOf());

	//	�����_�[�^�[�Q�b�g�r���[�̐ݒ�
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	//	�����_�[�^�[�Q�b�g�r���[�̐���
	deviceResources->GetD3DDevice()->CreateRenderTargetView(m_capture.Get(), &rtvDesc, &m_captureRTV);

	//	�V�F�[�_���\�[�X�r���[�̐ݒ�
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

	//	�����_�[�^�[�Q�b�g�r���[�Ɛ[�x�r���[���擾�i��Ō��ɖ߂����߁j
	ID3D11RenderTargetView* defaultRTV = deviceResources->GetRenderTargetView();
	ID3D11DepthStencilView* pDSV = deviceResources->GetDepthStencilView();

	// �w�i�F�̎擾(����)
	float backColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// �����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V���̐ݒ�
	context->OMSetRenderTargets(1, m_captureRTV.GetAddressOf(), pDSV);
	context->ClearRenderTargetView(m_captureRTV.Get(), backColor);
	context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);

	// �t�F�[�h�̎��Ԃ� 0 ~ 1�Ő��K��������
	float t = m_totalTime / FADE_TIME;

	// �t�F�[�h�̃T�C�Y���v�Z
	float size = CalcrateFadeValue(t);

	DirectX::SimpleMath::Matrix world;
	world = DirectX::SimpleMath::Matrix::CreateScale(size, size, 1.0f);

	// �V�F�[�_�[�ɓn�����̔}�̂��쐬����
	ConstBuffer cbuff;

	// �n���f�[�^��o�^����
	cbuff.matView = DirectX::SimpleMath::Matrix::Identity;						// �X�N���[�����W�ŕ`�悷�邽�ߕs�v
	cbuff.matProj = DirectX::SimpleMath::Matrix::Identity;						// �X�N���[�����W�ŕ`�悷�邽�ߕs�v
	cbuff.matWorld = world.Transpose();
	cbuff.Diffuse = DirectX::SimpleMath::Vector4::One;							// �e�N�X�`���̐F
	cbuff.time = DirectX::SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 0.0f);				// �t�F�[�h�̎��ԁi���v�f�̂ݎg�p�j

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// �V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* ccb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, ccb);
	context->GSSetConstantBuffers(0, 1, ccb);
	context->PSSetConstantBuffers(0, 1, ccb);

	//	�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//	�`�悷��I�u�W�F�N�g�̏���ݒ�
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),DirectX::SimpleMath::Vector4::One, DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
	};

	//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, m_stencilImage.GetAddressOf());

	//	�V�F�[�_���Z�b�g����
	context->VSSetShader(m_maskVS.Get(), nullptr, 0);
	context->GSSetShader(m_maskGS.Get(), nullptr, 0);
	context->PSSetShader(m_maskPS.Get(), nullptr, 0);

	//	�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_maskInputLayout.Get());

	// (���ۂɂ͕\�����Ȃ���) �`����s��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_batch->End();

	//	�`�悵����ʂ�captureSRV�ɕۑ�����
	deviceResources->GetD3DDevice()->CreateShaderResourceView
	(
		m_capture.Get(), &srvDesc, m_captureSRV.ReleaseAndGetAddressOf()
	);

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

	//	�ێ����Ă������f�t�H���g�ݒ�ɖ߂��āA��ʕ`�悪����ɏo����悤�ɂ��Ă���
	context->OMSetRenderTargets(1, &defaultRTV, pDSV);
	// �g�p�����������
	context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 0.0f, 0);

}
