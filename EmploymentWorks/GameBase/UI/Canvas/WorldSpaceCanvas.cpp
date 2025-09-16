/*
	�N���X��     : WorldSpaceCanvas
	����         :3D��ԗp��UI�pCanvas
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "WorldSpaceCanvas.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Screen.h"
#include "GameBase/Actor.h"
#include "GameBase/Component/UI/ImageComponent.h"
#include "GameBase/Component/BaseComponents.h"
#include "GameBase/Shader/ShaderFactory.h"
#include "GameBase/Camera/Camera.h"

/// <summary>
/// �C���v�b�g���C�A�E�g
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> WorldSpaceCanvas::INPUT_LAYOUT =
{
	 { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
WorldSpaceCanvas::WorldSpaceCanvas(Scene* scene)
	:
	Canvas(scene, RenderType::WorldSpace)
	, m_vertexShader{}
	, m_pixelShader{}
	, m_geometryShader{}
	, m_CBuffer{}
	, m_inputLayout{}
	,m_isBillboard{true}
{

	using namespace DirectX;

	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();


	//	�v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	auto shaderFactory = ShaderFactory::GetInstance();



	m_inputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "WorldSpaceUIVS.cso");

	//�e�V�F�[�_�[�̍쐬
	m_vertexShader = shaderFactory->CreateVS(device,   "WorldSpaceUIVS.cso");
	m_pixelShader = shaderFactory->CreatePS(device,    "WorldSpaceUIPS.cso");
	m_geometryShader = shaderFactory->CreateGS(device, "WorldSpaceUIGS.cso");


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
WorldSpaceCanvas::~WorldSpaceCanvas()
{

}

/// <summary>
/// �`��
/// </summary>
void WorldSpaceCanvas::Render(const Camera& camera)
{

	for (auto& com : GetImageComponent())
	{

		if (!com->GetActive()) continue;

		//�`���ނ��Ƃ�
		switch (com->GetRenderKinds())
		{
			case ImageComponent::RenderKinds::NORMAL:
				//�ʏ�`��
				NormalRender(camera,com);
				break;
			case ImageComponent::RenderKinds::CUSTOM:
				//�o�^���ꂽ�֐��̌Ăяo��
				com->GetCustomRenderFunction()();
				break;
			default:
				break;
		}
	}

}

/// <summary>
/// �ʏ�`��
/// </summary>
/// <param name="comp">�R���|�[�l���g</param>
void WorldSpaceCanvas::NormalRender(const Camera& camera,ImageComponent* comp)
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	auto states = CommonResources::GetInstance()->GetCommonStates();
	//���_
	VertexPositionTexture vertex[1] = {
			VertexPositionTexture(comp->GetActor()->GetTransform()->GetWorldPosition(),Vector2(comp->GetTextureWidth(),comp->GetTextureHeight()))
	};

	Matrix view;

	if (m_isBillboard)
	{
		//�r���{�[�h����
		view = camera.GetViewMatrix().Invert();
	}
	else
	{
		//�r���{�[�h�Ȃ�
		view = Matrix::Identity;
	}
	

	//�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	WorldSpaceCanvas::ConstBuffer cbuff;
	cbuff.matView = camera.GetViewMatrix().Transpose();
	cbuff.matProj = camera.GetProjectionMatrix().Transpose();
	cbuff.matWorld = view.Transpose() ;



	cbuff.Position = Vector4(0,1, 0, 0);
	cbuff.Size = Vector4(comp->GetWidth(), comp->GetHeight(), 1, 1);
	cbuff.Rotate = Vector4(comp->GetAngle(), 0, 0, 0);
	cbuff.Color = comp->GetColor();
	cbuff.CutRange = comp->GetCutRange();
	cbuff.ViewRange = comp->GetViewRange();
	cbuff.FillAmount = comp->GetFillAmount();



	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//�摜�p�T���v���[�̓o�^
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
	context->PSSetShaderResources(0, 1, comp->GetTexture().GetAddressOf());

	//	�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	//	�|���S����`��
	m_batch->Begin();
	//m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex, 1);
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], ARRAYSIZE(vertex));
	m_batch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);


}

