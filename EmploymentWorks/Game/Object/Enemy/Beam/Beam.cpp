/*
	@file	Beam.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Beam.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Object/Enemy/Beam/BeamRays.h"
#include "Game/Object/Enemy/Beam/BeamEnergyBall.h"
#include "Game/Object/Enemy/Beam/BeamChargeEffect.h"

#include "Game/DetectionCollision/CollisionManager.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;



const std::vector<D3D11_INPUT_ELEMENT_DESC> Beam::INPUT_LAYOUT =
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
Beam::Beam()
	:
	m_commonResources{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Beam::~Beam()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Beam::Initialize()
{

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	//BinaryFile VS = BinaryFile::LoadFile(L"Resources/Shaders/BeamVS.cso");
	//BinaryFile PS = BinaryFile::LoadFile(L"Resources/Shaders/BeamPS.cso");


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




	m_position = Vector3::Zero;

	//�r�[���̑���
	m_thickness = 0.9f;

	m_initialScale = Vector3(m_thickness, m_thickness, 0.0f);

	m_scale = m_initialScale;

	m_rotate = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(0.0f));

	m_target = Vector3(0, 0, 5);


	m_isHit = false;

	m_maxLength = 0.3f;

	float scale = 2.0f;

	m_chargyBallParamater->InitialScale = Vector3::Zero;

	m_chargyBallParamater->MaxScale = Vector3(1.0f, 1.0f, 1.0f) * scale;
	//�\������̎���
	m_chargyBallParamater->MaxPreliminaryActionTime = 2.0f;
	//�G�l���M�[�e�̗��ߎ���
	m_chargyBallParamater->AccumulationTime = 2.0f;

	m_chargyBallParamater->ChargeEffectCreateTime = 0.5f;

	m_chargyBallParamater->ShrinkTime = 0.6f;

	m_chargyBallParamater->MoveSpeed = 20.0f;


	m_raysParameter->InitialScale = Vector3(0.0f,0.0f,0.0f);

	m_raysParameter->MaxScale = Vector3(1.0, 1.0f, 0.0f) * scale;

	m_raysParameter->MoveSpeed = 1.0f;

	m_raysParameter->ShrinkTime = 0.6f;

	m_idling->Initialize();
	m_attack->Initialize();
	m_attackEnd->Initialize();
	m_preliminaryAction->Initialize();

	m_energyBall->Initialize();
	m_rays->Initialize();


	m_currentState = m_idling.get();

	m_isHit = false;

	m_classState = CurrentClassState::Idling;

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Beam::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	m_currentState->Update(elapsedTime);

	//for (auto& particle : m_chargeEffect)
	//{
	//	particle->Update(elapsedTime);


	//}

		//�G�̌��݂̍��W�̎擾
	Vector3 startPosition = m_position;
	//�v���C���̌��݂̍��W�̎擾
	Vector3 endPosition = m_target;
	//�G����v���C���̕����x�N�g���̌v�Z
	Vector3 toPlayer = endPosition - startPosition;
	//yaw�̌v�Z�@�i���E��]�j
	//xz���ʂœG����v���C���̕��������߂�
	float yaw = atan2(toPlayer.x, toPlayer.z);
	//pitch�̌v�Z�i�㉺��]�j
	//�G����v���C���̃E�ᒺ���������߂�
	float pitch = atan2(toPlayer.y, sqrt(toPlayer.x * toPlayer.x + toPlayer.z * toPlayer.z));

	//yaw pitch�����]���v�Z pitch�͔��]������
	m_rotate = Quaternion::CreateFromYawPitchRoll(yaw, -pitch, 0.0f);


	


	for (auto& effect : m_deleteChargeEffect)
	{
		m_chargeEffect.erase(
			std::remove_if(
				m_chargeEffect.begin(), m_chargeEffect.end(),
				[&effect](const std::unique_ptr<BeamChargeEffect>& particle) {
					return particle.get() == effect; // ��v���邩�𔻒�
				}
			),
			m_chargeEffect.end()
		);
	}

	m_deleteChargeEffect.clear();


	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	if (kbTracker->released.E)
	{
		ChangeState(m_attackEnd.get());
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Beam::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();




	switch (m_classState)
	{
		case Beam::Idling:
			break;
		case Beam::PreliminaryAction:
			m_energyBall->Render(view, projection);
			for (auto& partcle : m_chargeEffect)
			{
				partcle->Render(view, projection);
			}
			break;
		case Beam::Attack:
			m_energyBall->Render(view, projection);
			m_rays->Render(view, projection);

			break;
		case Beam::AttackEnd:
			m_energyBall->Render(view, projection);
			m_rays->Render(view, projection);

			break;
		default:
			break;
	}
	

	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Beam::Finalize()
{
	// do nothing.
}

void Beam::RegistrationInformation(CommonResources* resources)
{

	m_commonResources = resources;

	m_idling->RegistrationInformation(m_commonResources, this);
	m_attack->RegistrationInformation(m_commonResources, this);
	m_attackEnd->RegistrationInformation(m_commonResources, this);
	m_preliminaryAction->RegistrationInformation(m_commonResources, this);
	m_energyBall->RegistrationInformation(m_commonResources, this);
	m_rays->RegistrationInformation(m_commonResources, this);


}

void Beam::Instances()
{

	m_idling = std::make_unique<Beamldling>();
	m_attack = std::make_unique<BeamAttack>();
	m_attackEnd = std::make_unique<BeamAttackEnd>();
	m_preliminaryAction = std::make_unique<BeamPreliminaryAction>();
	m_energyBall = std::make_unique<BeamEnergyBall>();
	m_rays = std::make_unique<BeamRays>();

	m_chargyBallParamater = std::make_unique<Beam::ChargyBallParamater>();

	m_raysParameter = std::make_unique<RaysParameter>();




}

void Beam::RegistrationCollionManager(CollisionManager* collsionManager)
{

	m_energyBall->RegistrationCollionManager(collsionManager);

}

void Beam::ChangeState(IBeamState* nextState)
{
	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();

}

void Beam::CreateParticle()
{

	std::vector<Vector3> position;
	std::vector<Quaternion> rotate;


	float radius = 0.9f;

	for (int angle = 0; angle < 360; angle += 45)
	{
		// �p�x�����W�A���ɕϊ�   �X�^�[�g���ォ��n�߂邽�߂ɂX�O�x�v���X����@�X�O�����Ȃ��ƉE����n�܂�
		float radian = DirectX::XMConvertToRadians(angle) + DirectX::XMConvertToRadians(90);

		// ���W���v�Z�i�ォ�甽���v���ɂ���j
		float x = radius * cos(radian); // X���W
		float y = radius * sin(radian); // Y���W

		// ���W��ǉ�
		position.push_back(Vector3(x, y, 0.0f));

		// ��]��ǉ��i���W�Ɠ�����ŉ�]���쐬�j
		rotate.push_back(Quaternion::CreateFromAxisAngle(Vector3::UnitZ, DirectX::XMConvertToRadians(angle)));

	}


	for (int i = 0; i < position.size(); i++)
	{
		auto particle = std::make_unique<BeamChargeEffect>();
		particle->RegistrationInformation(m_commonResources, this);
		particle->Initialize(position[i], rotate[i]);

		m_chargeEffect.push_back(std::move(particle));

	}
}

void Beam::RegistrationDeleteParticle(BeamChargeEffect* effect)
{
	m_deleteChargeEffect.push_back(effect);

}

void Beam::DeleteParticle()
{

	m_chargeEffect.clear();

}


