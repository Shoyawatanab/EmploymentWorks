#include "pch.h"
#include "PlayerDamageEffect.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Shader/ShaderFactory.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"
#include "Game/Messenger/Scene/SceneMessages.h"

///	<summary>
///	�C���v�b�g���C�A�E�g
///	</summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> PlayerDamageEffect::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene"></param>
PlayerDamageEffect::PlayerDamageEffect(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_alpha{1.0f}
	,m_image{}
{

	//�R���e�L�X�g�̎擾
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();


	m_image = GetScene()->AddActor<Image>(canvas,"HP");
	m_image->SetCustomRenderFunction(std::bind(&PlayerDamageEffect::CustomRender, this));


	CreateShader();

	//	�v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(context);

	m_image->SetActive(false);

	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::PLAYER_DAMAGE
		}, this
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerDamageEffect::~PlayerDamageEffect()
{
}

/// <summary>
/// �ʃA�b�v�f�[�g
/// </summary>
/// <param name="deltaTime"></param>
void PlayerDamageEffect::UpdateActor(const float& deltaTime)
{
	//�����x�̍X�V
	m_alpha -= deltaTime * 1.0f;

	//�����ɂȂ�����
	if (m_alpha <= 0)
	{
		m_image->SetActive(false);
	}
}

/// <summary>
/// �J�X�^���`��
/// </summary>
void PlayerDamageEffect::CustomRender()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//�R���e�L�X�g�̎擾
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//�f�o�C�X�̎擾
	auto states = CommonResources::GetInstance()->GetCommonStates();


	//	���_���(�|���S���̂S���_�̍��W���j
	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(Vector3(0.0f,  0.0f, 0.0f),Vector4::One,Vector2(0.0f, 0.0f)),
	};

	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.matView = Matrix::Identity;
	cbuff.matProj = Matrix::Identity;
	cbuff.matWorld = Matrix::Identity;
	cbuff.Diffuse = Vector4(1, 1, 1, 1);
	cbuff.Time = Vector4(m_alpha, 0.0f, 0.0f, 0.0f);

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_cBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_cBuffer.Get() };
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
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void PlayerDamageEffect::Notify(SceneMessageType type, void* datas)
{

	switch (type)
	{
		case SceneMessageType::PLAYER_DAMAGE:
			Begin();
			break;
		default:
			break;
	}

}

/// <summary>
/// �V�F�[�_�[�쐬
/// </summary>
void PlayerDamageEffect::CreateShader()
{
	//�V�F�[�_�[�̍쐬
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();


	auto shaderFactory = ShaderFactory::GetInstance();


	//�e�V�F�[�_�[�̍쐬
	m_vertexShader = shaderFactory->CreateVS(device, "DamageVignetteVS.cso");
	m_pixelShader = shaderFactory->CreatePS(device, "DamageVignettePS.cso");
	m_geometryShader = shaderFactory->CreateGS(device, "DamageVignetteGS.cso");

	m_inputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "DamageVignetteVS.cso");

	//	�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_cBuffer);

}

/// <summary>
/// �J�n
/// </summary>
void PlayerDamageEffect::Begin()
{

	m_image->SetActive(true);
	m_alpha = 1.0f;

}
