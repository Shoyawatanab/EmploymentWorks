/*
	@file	Ceiling.cpp
	@brief	
*/
#include "pch.h"
#include "Ceiling.h"
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


//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Ceiling::Ceiling()
	:
	m_commonResources{}
	,m_scale{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Ceiling::~Ceiling()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Ceiling::Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Scale, DirectX::SimpleMath::Vector3 Rotate)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;
	m_position = position;
	m_scale = Scale;
	m_rotate = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(Rotate.z), DirectX::XMConvertToRadians(Rotate.y), DirectX::XMConvertToRadians(Rotate.x));


	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();


	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Stage.cmo", *fx);



	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, m_scale);
	m_bounding->CreateBoundingSphere(m_commonResources,m_position, 20.0f);

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Ceiling::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	using namespace DirectX;
	using namespace DirectX::SimpleMath;

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Ceiling::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
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


	//m_bounding->DrawBoundingSphere(m_position, view, projection);
	m_bounding->DrawBoundingBox(m_position, view, projection);



}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Ceiling::Finalize()
{
	// do nothing.
}


void Ceiling::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}



void Ceiling::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(PartnerTag);
	UNREFERENCED_PARAMETER(Pos);
}

