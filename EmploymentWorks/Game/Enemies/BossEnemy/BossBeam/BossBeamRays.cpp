/*
	@file	BossBeamRays.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BossBeamRays.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/BinaryFile.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;



const std::vector<D3D11_INPUT_ELEMENT_DESC> BossBeamRays::INPUT_LAYOUT =
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
BossBeamRays::BossBeamRays(Scene* scene)
	:
	Actor(scene)
	,m_model{}
	,m_vertexShader{}
	,m_pixelShader{}
	,m_inputLayout{}
	,m_CBuffer{}
	,m_initialScale{}
	,m_initialPosition{}
	,m_initialRotate{}
	,m_target{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossBeamRays::~BossBeamRays()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
void BossBeamRays::Initialize()
{


	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();


	BinaryFile VS = BinaryFile::LoadFile(L"Resources/Shaders/BossBeamRaysVS.cso");
	BinaryFile PS = BinaryFile::LoadFile(L"Resources/Shaders/BossBeamRaysPS.cso");


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
	//m_model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("Beam");

	m_initialScale = Vector3::Zero;


	m_initialRotate = Quaternion::Identity;

	m_target = Vector3(0, 0, 5);


	m_isHit = false;




}






