/*
	@file	Enemy.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Enemy.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Libraries/MyLib/Bounding.h"
#include "Game/DetectionCollision/CollisionManager.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Enemy::Enemy()
	:
	m_commonResources{},
	m_model{},
	m_position{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Enemy::~Enemy()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Enemy::Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position)
{
	using namespace DirectX::SimpleMath;


	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();




	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Enemy.cmo", *fx);

	m_position = position;

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, Vector3(0.5f, 0.9f, 0.5f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 1.0f);

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Enemy::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();


}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Enemy::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	// ���[���h�s����X�V����
	Matrix world = Matrix::CreateScale(0.3f);
	world *= Matrix::CreateTranslation(m_position);


	// ���f����`�悷��
	m_model->Draw(context, *states, world, view, projection);

	m_bounding->DrawBoundingBox(m_position, view, projection);
	m_bounding->DrawBoundingSphere(m_position, view, projection);



}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Enemy::Finalize()
{
	// do nothing.
}



void Enemy::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}

