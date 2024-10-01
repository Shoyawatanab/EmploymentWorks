/*
	@file	Tree1.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Tree1.h"
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

#include "FrameWork/Resources.h"

#include "Libraries/MyLib/CollisionMesh.h"

const DirectX::SimpleMath::Vector3 POS(0.0f, 0.0f, 0.0f);
const float SCALE(8.0f);

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Tree1::Tree1()
	:
	m_commonResources{},
	m_model{},
	m_scale{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Tree1::~Tree1()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Tree1::Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Extens, float Scale)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;
	m_position = position;
	m_scale = Scale;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// ���f����ǂݍ���
	//m_model = Resources::GetInstance()->GetTree1Model();

		// ���\�[�X�f�B���N�g����ݒ肷��
	std::unique_ptr<DirectX::EffectFactory> tree1Fx = std::make_unique<DirectX::EffectFactory>(device);
	tree1Fx->SetDirectory(L"Resources/Models");

	// �u�؂P�v���f�������[�h����
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Tree1.cmo", *tree1Fx);


	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, Extens);
	m_bounding->CreateBoundingSphere(m_commonResources, m_position + Vector3(0,8,0), 9.0f);

	// �R���W�������b�V���𐶐�����
	m_collisionMesh = std::make_unique<mylib::CollisionMesh>();
	//��̃��b�V���̓ǂݍ���
	m_collisionMesh->Initialize(device, context, L"Tree1Mesh", m_position, m_scale);

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Tree1::Update(float elapsedTime, DirectX::SimpleMath::Quaternion cameraRotation)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	UNREFERENCED_PARAMETER(cameraRotation);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Tree1::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX::SimpleMath;
	using namespace DirectX;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();




	// ���[���h�s����X�V����
	Matrix world = Matrix::CreateScale(m_scale);
	world *= Matrix::CreateTranslation(m_position);
	// ���f����`�悷��
	m_model->Draw(context, *states, world, view, projection);
	m_bounding->DrawBoundingSphere(POS, view, projection);
	//m_bounding->DrawBoundingBox(m_position, view, projection);


	//// ���b�V����`�悷��
	//m_collisionMesh->Draw(context, states, view, projection);


}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Tree1::Finalize()
{
	// do nothing.
}


void Tree1::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}


void Tree1::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(PartnerTag);
	UNREFERENCED_PARAMETER(Pos);
}

