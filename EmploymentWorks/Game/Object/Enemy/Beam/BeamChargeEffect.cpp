/*
	@file	BeamChargeEffect.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BeamChargeEffect.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Object/Enemy/Beam/Beam.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



const std::vector<D3D11_INPUT_ELEMENT_DESC> BeamChargeEffect::INPUT_LAYOUT =
{
	{ "POSITION",    0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",       0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
BeamChargeEffect::BeamChargeEffect()
	:
	m_commonResources{},
	m_model{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
BeamChargeEffect::~BeamChargeEffect()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void BeamChargeEffect::Initialize(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotate)
{

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	//BinaryFile VS = BinaryFile::LoadFile(L"Resources/Shaders/BeamChargeEffectVS.cso");
	//BinaryFile PS = BinaryFile::LoadFile(L"Resources/Shaders/BeamChargeEffectPS.cso");


	////	�C���v�b�g���C�A�E�g�̍쐬
	//device->CreateInputLayout(&INPUT_LAYOUT[0],
	//	static_cast<UINT>(INPUT_LAYOUT.size()),
	//	VS.GetData(), VS.GetSize(),
	//	m_inputLayout.ReleaseAndGetAddressOf());


	//DX::ThrowIfFailed(
	//	device->CreateVertexShader(
	//		VS.GetData(),
	//		VS.GetSize(),
	//		nullptr,
	//		m_vertexShader.ReleaseAndGetAddressOf())
	//);


	//DX::ThrowIfFailed(
	//	device->CreatePixelShader(
	//		PS.GetData(),
	//		PS.GetSize(),
	//		nullptr,
	//		m_pixelShader.ReleaseAndGetAddressOf())
	//);

	////	�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	//D3D11_BUFFER_DESC bd;
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(ConstBuffer);
	//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;

	//device->CreateBuffer(&bd, nullptr, &m_CBuffer);



	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BeamChargeEffect.cmo", *fx);

	m_position = position;

	//�r�[���̑���
	float a = 0.1f;

	m_initialScale = Vector3(a, a, a);

	m_scale = m_initialScale;

	m_initialRotate = rotate;

	m_target = Vector3(0, 0, 5);





	m_isHit = false;

	m_maxLength = 0.3f;




}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void BeamChargeEffect::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	Vector3 beamPosition = m_beam->GetPosition();

	//���S�Ɍ������Ĉړ�������
	Vector3 direction = Vector3::Zero - m_position;
	direction.Normalize();

	direction *= elapsedTime * 1.0f;

	m_position += direction;

	float distance = Vector3::Distance(beamPosition, m_position);


	if (distance < 0.1f)
	{
		m_beam->RegistrationDeleteParticle(this);
	}

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void BeamChargeEffect::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();



	// ���[���h�s����X�V����
	Matrix world = Matrix::Identity;
	world *= Matrix::CreateScale(m_scale);
	world *= Matrix::CreateFromQuaternion(m_initialRotate);
	world *= Matrix::CreateTranslation(m_position);
	world *= Matrix::CreateFromQuaternion(m_beam->GetRotate());
	world *= Matrix::CreateTranslation(m_beam->GetPosition());

	//���f����`�悷��
	m_model->Draw(context, *states, world, view, projection, false, [&]()
		{

			//ConstBuffer cbuff;
			//cbuff.matWorld = world.Transpose();

			//cbuff.matView = view.Transpose();
			//cbuff.matProj = projection.Transpose();

			//context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

			//ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
			//context->VSSetConstantBuffers(0, 1, cb);
			//context->PSSetConstantBuffers(0, 1, cb);

			//context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

			//////	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
			//context->OMSetDepthStencilState(states->DepthDefault(), 0);

			//////	�J�����O�͂Ȃ�
			//context->RSSetState(states->CullNone());


			//context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
			//context->PSSetShader(m_pixelShader.Get(), nullptr, 0);


			//context->IASetInputLayout(m_inputLayout.Get());

		});

	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void BeamChargeEffect::Finalize()
{
	// do nothing.
}

void BeamChargeEffect::RegistrationInformation(CommonResources* resoure, Beam* beam)
{

	m_commonResources = resoure;
	m_beam = beam;
}

