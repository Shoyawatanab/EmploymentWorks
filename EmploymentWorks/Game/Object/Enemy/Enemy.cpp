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
	m_position{},
	m_hp{},
	m_currentState{},
	m_idling{},
	m_move{},
	m_attack{}
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
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/kariEnemy.cmo", *fx);

	m_position = position;
	
	m_idling = std::make_unique<EnemyIdling>(this);
	m_idling->Initialize();
	m_move = std::make_unique<EnemyMove>(this);
	m_move->Initialize();
	m_attack = std::make_unique<EnemyAttack>(this);
	m_attack->Initialize();

	m_currentState = m_idling.get();

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, Vector3(3.5f, 4.9f, 1.8f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 6.0f);

	m_hp = 2;
	m_maxHP = m_hp;
	m_graivty = 0.05f;
	m_scale = 1.8f;
	m_isCollsionTime = false;
	m_collisionTime = 0;

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Enemy::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();

	m_currentState->Update(elapsedTime);

	if (m_isCollsionTime)
	{
		m_collisionTime += elapsedTime;
		if (m_collisionTime >= 6)
		{
			m_isCollsionTime = false;
			m_collisionTime = 0;
		}
	}


	if (m_hp <= 0 && m_scale > 0)
	{
		m_scale -= 0.01f;

	}
	else
	{
		m_position.y -= m_graivty;
	}

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
	Matrix world = Matrix::CreateScale(m_scale);
	world *= Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
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

void Enemy::ChangeState(IEnemyState* nextState)
{
	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();
}



void Enemy::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}

void Enemy::OnCollision(CollsionObjectTag& PartnerTag)
{
	//�u�[�������Ɠ������Ƃ��ɖ��t���[��Hp���ւ�Ȃ��悤�ɂ���
	if (m_isCollsionTime)
	{
		return;
	}

	m_hp--;

	m_isCollsionTime = true;
}