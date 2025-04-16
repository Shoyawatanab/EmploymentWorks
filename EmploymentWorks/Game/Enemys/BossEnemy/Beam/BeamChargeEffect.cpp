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
#include "Libraries/WataLib/GameResources.h"
#include <cassert>
#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/Params.h"

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

/// <summary>
/// �R���X�g���N�^
/// </summary>
BeamChargeEffect::BeamChargeEffect()
	:
	m_commonResources{},
	m_model{}
	,m_vertexShader{}
	,m_pixelShader{}
	,m_inputLayout{}
	,m_CBuffer{}
	,m_position{}
	,m_scale{}
	,m_initialPosition{}
	,m_initialScale{}
	,m_initialRotate{}
	,m_beam{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BeamChargeEffect::~BeamChargeEffect()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
/// <param name="resoure">���ʃ��\�[�X</param>
/// <param name="position">���W</param>
/// <param name="rotate">��]</param>
void BeamChargeEffect::Initialize(CommonResources* resoure,DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotate)
{
	m_commonResources = resoure;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// ���f����ǂݍ���
	m_model = m_commonResources->GetGameResources()->GetModel("BeamChargeEffect");

	m_position = position;

	//�r�[���̑���
	float a = 0.1f;

	m_initialScale = Vector3(a, a, a);

	m_scale = m_initialScale;

	m_initialRotate = rotate;

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BeamChargeEffect::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	Vector3 beamPosition = m_beam->GetPosition();

	//���S�Ɍ������Ĉړ�������
	Vector3 direction = Vector3::Zero - m_position;
	direction.Normalize();

	direction *= elapsedTime * Params::BOSSENEMY_BEAM_CHARGE_EFFECT_MOVE_TIME;

	m_position += direction;

	float distance = Vector3::Distance(beamPosition, m_position);


	if (distance < 0.1f)
	{
		m_beam->RegistrationDeleteParticle(this);
	}

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void BeamChargeEffect::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();



	// ���[���h�s����X�V����
	Matrix world = Matrix::Identity;
	world *= Matrix::CreateScale(m_scale);
	world *= Matrix::CreateFromQuaternion(m_initialRotate);
	world *= Matrix::CreateTranslation(m_position);
	world *= Matrix::CreateFromQuaternion(m_beam->GetRotation());
	world *= Matrix::CreateTranslation(m_beam->GetPosition());

	//���f����`�悷��
	m_model->Draw(context, *states, world, view, projection, false, [&]()
		{
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

/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="beam">�r�[��</param>
void BeamChargeEffect::AddPointer(Beam* beam)
{
	m_beam = beam;

}

