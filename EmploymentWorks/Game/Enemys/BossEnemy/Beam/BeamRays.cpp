/*
	@file	BeamRays.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BeamRays.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/WataLib/GameResources.h"
#include <cassert>
#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



const std::vector<D3D11_INPUT_ELEMENT_DESC> BeamRays::INPUT_LAYOUT =
{
	{ "POSITION",    0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",       0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="parent">�e</param>
BeamRays::BeamRays(CommonResources* resources, BaseEntity* parent)
	:
	BaseEntity(resources, Vector3::One, Vector3::Zero, Quaternion::Identity),
	m_model{}
	,m_vertexShader{}
	,m_pixelShader{}
	,m_inputLayout{}
	,m_CBuffer{}
	,m_initialScale{}
	,m_initialPosition{}
	,m_initialRotate{}
	,m_target{}
{
	BaseEntity::SetParent(parent);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BeamRays::~BeamRays()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
void BeamRays::Initialize()
{

	BaseEntity::Initialize();

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();


	BinaryFile VS = BinaryFile::LoadFile(L"Resources/Shaders/BeamRaysVS.cso");
	BinaryFile PS = BinaryFile::LoadFile(L"Resources/Shaders/BeamRaysPS.cso");


	//	�C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VS.GetData(), VS.GetSize(),
		m_inputLayout.ReleaseAndGetAddressOf());


	DX::ThrowIfFailed(
		device->CreateVertexShader(
			VS.GetData(),
			VS.GetSize(),
			nullptr,
			m_vertexShader.ReleaseAndGetAddressOf())
	);



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


	// ���f����ǂݍ���
	m_model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("Beam");

	m_initialScale = Vector3::Zero;

	BaseEntity::SetScale(m_initialScale);

	m_initialRotate = Quaternion::Identity;

	m_target = Vector3(0, 0, 5);


	m_isHit = false;




}


/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void BeamRays::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	//�I�u�W�F�N�g���`�悪�����Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}


	BaseEntity::Render(view, projection);

	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();




	Vector4 color = Vector4(1, 1, 1, 1);


	//���f����`�悷��
	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection, false, [&]()
		{


			ConstBuffer cbuff;
			cbuff.matWorld = BaseEntity::GetWorldMatrix().Transpose();

			cbuff.matView = view.Transpose();
			cbuff.matProj = projection.Transpose();
			cbuff.Color = color;


			context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

			ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
			context->VSSetConstantBuffers(0, 1, cb);
			context->PSSetConstantBuffers(0, 1, cb);

			context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

			////	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
			context->OMSetDepthStencilState(states->DepthDefault(), 0);

			////	�J�����O�͂Ȃ�
			context->RSSetState(states->CullNone());


			context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
			context->PSSetShader(m_pixelShader.Get(), nullptr, 0);


			context->IASetInputLayout(m_inputLayout.Get());


		});


	Vector3 s = BaseEntity::GetScale();
	s.y *= 1.1f;
	s.x *= 1.1f;
	Matrix world;
	world = Matrix::CreateScale(s);
	world *= Matrix::CreateFromQuaternion(BaseEntity::GetRotation());
	world *= Matrix::CreateTranslation(BaseEntity::GetPosition());

	color = Vector4(1, 0, 0, 1);

	//���f����`�悷��
	m_model->Draw(context, *states, world, view, projection, false, [&]()
		{

			ConstBuffer cbuff;
			cbuff.matWorld = world.Transpose();

			cbuff.matView = view.Transpose();
			cbuff.matProj = projection.Transpose();
			cbuff.Color = color;


			context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

			ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
			context->VSSetConstantBuffers(0, 1, cb);
			context->PSSetConstantBuffers(0, 1, cb);

			context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

			////	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
			context->OMSetDepthStencilState(states->DepthDefault(), 0);

			////	�J�����O�͂Ȃ�
			context->RSSetState(states->CullClockwise());


			context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
			context->PSSetShader(m_pixelShader.Get(), nullptr, 0);


			context->IASetInputLayout(m_inputLayout.Get());
		});



	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BeamRays::Update(const float& elapsedTime)
{
	//�I�u�W�F�N�g���X�V�������Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}


	BaseEntity::Update(elapsedTime);

}





