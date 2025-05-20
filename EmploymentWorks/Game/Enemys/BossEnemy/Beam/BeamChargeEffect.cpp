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
/// <param name="resoure">���ʃ��\�[�X</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotate">��]</param>
BeamChargeEffect::BeamChargeEffect(CommonResources* resoure, DirectX::SimpleMath::Vector3 scale,DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotate)
	:
	BaseEntity(resoure, scale,position,rotate)
	,m_model{}
	,m_vertexShader{}
	,m_pixelShader{}
	,m_inputLayout{}
	,m_CBuffer{}
	,m_initialPosition{}
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
void BeamChargeEffect::Initialize()
{

	// ���f����ǂݍ���
	m_model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BeamChargeEffect");



}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BeamChargeEffect::Update(const float& elapsedTime)
{

	using namespace DirectX::SimpleMath;

	//�I�u�W�F�N�g���X�V�������Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}


	Vector3 beamPosition = m_beam->GetPosition();

	Vector3 position =  BaseEntity::GetLocalPosition();

	//���S�Ɍ������Ĉړ�������
	Vector3 direction = Vector3::Zero - position;
	direction.Normalize();

	direction *= elapsedTime * Params::BOSSENEMY_BEAM_CHARGE_EFFECT_MOVE_TIME;

	position += direction;

	BaseEntity::SetLocalPosition(position);

	float distance = Vector3::Distance(beamPosition, BaseEntity::GetPosition());


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
	using namespace DirectX::SimpleMath;
	
	//�I�u�W�F�N�g���`�悪�����Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}


	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();



	// ���[���h�s����X�V����
	BaseEntity::Render(view,projection);

	//���f����`�悷��
	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection, false, [&]()
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

/// <summary>
/// �����ɂȂ�����
/// </summary>
void BeamChargeEffect::OnDisable()
{
	m_beam->RegistrationDeleteParticle(this);

}

