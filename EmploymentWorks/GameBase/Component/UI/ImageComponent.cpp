#include "pch.h"
#include "ImageComponent.h"
#include "GameBase/Actor.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Managers.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/GameResources.h"
#include "GameBase/Shader/ShaderFactory.h"
#include "Libraries/MyLib/BinaryFile.h"
#include "GameBase/Screen.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// �C���v�b�g���C�A�E�g
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> ImageComponent::INPUT_LAYOUT =
{
	 { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};




ImageComponent::ImageComponent(Actor* owner, std::string textureName)
	:
	Component(owner)
	,m_texture{}
	,m_CBuffer{}
	,m_inputLayout{}
	, m_vertexShader{}
	,m_pixelShader{}
	,m_geometryShader{}
	,m_textureHeight{}
	,m_textureWidth{}
	,m_color{DirectX::SimpleMath::Vector4(1.0f,1.0f,1.0f,1.0f)}
	,m_cutRange{DirectX::SimpleMath::Vector4(0.0f,0.0f,1.0f,1.0f)}
	,m_viewRange{DirectX::SimpleMath::Vector4::One}
	,m_fillAmount{DirectX::SimpleMath::Vector4::One}
	,m_renderKinds{RenderKinds::NORMAL}
{

	using namespace DirectX;


	//�}�l�[�W���[�ɒǉ�
	GetActor()->GetScene()->GetRenderMangaer()->AddUserInterface(this);

	LoadTexture(textureName);


	//�V�F�[�_�[�̍쐬
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();


	auto shaderFactory = ShaderFactory::GetInstance();

	//�e�V�F�[�_�[�̍쐬
	m_vertexShader = shaderFactory->CreateVS(device, "UIVS.cso");
	m_pixelShader = shaderFactory->CreatePS(device, "UIPS.cso");
	m_geometryShader = shaderFactory->CreateGS(device, "UIGS.cso");

	m_inputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "UIVS.cso");


	//	�v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);


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
/// �f�X�g���N�^
/// </summary>
ImageComponent::~ImageComponent()
{
}


void ImageComponent::Render()
{

	switch (m_renderKinds)
	{
		case ImageComponent::RenderKinds::NORMAL:
			NormalRender();
			break;
		case ImageComponent::RenderKinds::CUSTOM:
			CustomRender();
			break;
		default:
			break;
	}

}



void ImageComponent::LoadTexture(std::string textureName)
{

	//�摜�̓ǂݍ���
	m_texture = GameResources::GetInstance()->GetTexture(textureName);

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
	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;
}

void ImageComponent::NormalRender()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	auto states = CommonResources::GetInstance()->GetCommonStates();



	VertexPositionTexture vertex{};

	//�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.windowSize = SimpleMath::Vector4(Screen::WIDTH, Screen::HEIGHT, 0, 0);
	cbuff.Position = Vector4(GetActor()->GetTransform()->GetWorldPosition().x, GetActor()->GetTransform()->GetWorldPosition().y, 0, 0);
	cbuff.Size = Vector4(GetWidth(), GetHeight(), 0, 0);
	cbuff.Color = m_color;
	cbuff.CutRange = m_cutRange;
	cbuff.ViewRange = m_viewRange;
	cbuff.FillAmount = m_fillAmount;

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
	context->OMSetDepthStencilState(states->DepthNone(), 0);

	context->RSSetState(states->CullNone());

	//	�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());


	//	�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());


	//	�|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex, 1);
	m_batch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

/// <summary>
/// �J�X�^���`��
/// </summary>
void ImageComponent::CustomRender()
{
	m_customRender();
}

/// <summary>
/// �����̎擾
/// </summary>
/// <returns></returns>
float ImageComponent::GetWidth() const
{
	return m_textureWidth * GetActor()->GetTransform()->GetWorldScale().x;
}

/// <summary>
/// �c���̎擾
/// </summary>
/// <returns></returns>
float ImageComponent::GetHeight() const
{
	return m_textureHeight * GetActor()->GetTransform()->GetWorldScale().y;
}


/// <summary>
/// �J�X�^���`��֐��̓o�^
/// </summary>
/// <param name="customRender">�֐�</param>
void ImageComponent::SetCustomRenderFunction(std::function<void()> customRender)
{

	m_customRender = customRender;
	//��Ԃ̕ύX
	m_renderKinds = RenderKinds::CUSTOM;
}
