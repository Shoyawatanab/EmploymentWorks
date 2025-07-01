#include "pch.h"
#include "GameOverBackGraund.h"
#include "GameBase/Shader/ShaderFactory.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/GameResources.h"
#include "GameBase/Common/Commons.h"
///	<summary>
///	�C���v�b�g���C�A�E�g
///	</summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> GameOverBackGraund::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};



/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas"></param>
GameOverBackGraund::GameOverBackGraund(Canvas* canvas)
	:
	Image(canvas,"ClearBackGraund")
	,m_time{}
{
	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);

	//�V�F�[�_�[�̍쐬
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	CreateShader(device, context);

	LoadTexture();

	//	�v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(context);

	auto comp = GetComponent<ImageComponent>();

	comp->SetCustomRenderFunction(std::bind(& GameOverBackGraund::CustomRender, this));

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameOverBackGraund::~GameOverBackGraund()
{
}

/// <summary>
/// �P�̍X�V
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void GameOverBackGraund::UpdateActor(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	m_time += deltaTime;

	m_time = std::min(m_time, ANIMATION_TIME);

	if (m_time == ANIMATION_TIME)
	{

		for (auto& actor : m_actor)
		{
			if (!actor->GetActive())
			{
				actor->SetActive(true);
			}
		}

	}

}

/// <summary>
/// �A�N�e�B�u��ԂɂȂ�����
/// </summary>
void GameOverBackGraund::OnEnable()
{
	m_time = 0.0f;
}

/// <summary>
/// �`��
/// </summary>
void GameOverBackGraund::CustomRender()
{

	//�V�F�[�_�[�̍쐬
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = CommonResources::GetInstance()->GetCommonStates();


	//���_���(�|���S���̂S���_�̍��W���j
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
	cbuff.time = DirectX::SimpleMath::Vector4(m_time, ANIMATION_TIME, 1, 1);

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

	//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	//�C���v�b�g���C�A�E�g�̓o�^
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

void GameOverBackGraund::CreateShader(ID3D11Device1* device, ID3D11DeviceContext* context)
{

	auto shaderFactory = ShaderFactory::GetInstance();
	//�e�V�F�[�_�[�̍쐬
	m_vertexShader = shaderFactory->CreateVS(device, "GameOverVS.cso");
	m_pixelShader = shaderFactory->CreatePS(device, "GameOverPS.cso");
	m_geometryShader = shaderFactory->CreateGS(device, "GameOverGS.cso");

	m_inputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "GameOverVS.cso");

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
/// �摜�̓ǂݍ���
/// </summary>
void GameOverBackGraund::LoadTexture()
{
	//�摜�̓ǂݍ���
	m_texture = GameResources::GetInstance()->GetTexture("GameOver");

	//�V�F�[�_�[���\�[�X�r���[����摜���̎擾
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	m_texture->GetResource(&resource);

	//���\�[�X��Texture2D�ɃL���X�g
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(resource.As(&tex));

	//�摜�����擾
	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	//�摜�̃T�C�Y���擾
	//m_textureWidth = desc.Width;
	//m_textureHeight = desc.Height;

}

