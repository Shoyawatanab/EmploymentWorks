/*
	@file	Pillar.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Pillar.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Game/DetectionCollision/CollisionManager.h"
#include "Libraries/MyLib/Bounding.h"

const DirectX::SimpleMath::Vector3 POS(0.0f, 0.0f, 0.0f);
const float SCALE(8.0f);

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Pillar::Pillar()
	:
	m_commonResources{},
	m_model{},
	m_scale{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Pillar::~Pillar()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Pillar::Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Scale, DirectX::SimpleMath::Vector3 Rotate, float BoundingSphereRadius)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;
	m_position = position;
	m_scale = Scale;
	m_rotate = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(Rotate.x), DirectX::XMConvertToRadians(Rotate.y), DirectX::XMConvertToRadians(Rotate.z));

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Pillar.cmo", *fx);

	Vector3 boxScale = m_scale;

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, boxScale);
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, BoundingSphereRadius);



}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Pillar::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Pillar::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	// ���[���h�s����X�V����
	Matrix world = Matrix::CreateScale(m_scale);
	world *= Matrix::CreateFromQuaternion(m_rotate);
	world *= Matrix::CreateTranslation(m_position);
	// ���f����`�悷��
	m_model->Draw(context, *states, world, view, projection);
	//m_bounding->DrawBoundingSphere(view, projection);
	m_bounding->DrawBoundingBox( view, projection);



}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Pillar::Finalize()
{
	// do nothing.
}


void Pillar::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}


void Pillar::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(PartnerTag);
	UNREFERENCED_PARAMETER(Pos);
}

