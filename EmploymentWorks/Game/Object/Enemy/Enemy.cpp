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
#include "Game/BehaviorTree/BehaviorTree.h"
#include "Game/Object/Player.h"

//�����̃^�[�Q�b�g�̍��W�̋���
static const DirectX::SimpleMath::Vector3 STAETTAEGETDIRECTION = DirectX::SimpleMath::Vector3(0, 0, 2.5f);


//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Enemy::Enemy()
	:
	m_commonResources{},
	m_model{},
	m_position{},
	m_hp{},
	m_behavior{},
	m_player{},
	m_knockbackDirection{},
	m_targetPos{}

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
	

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, Vector3(3.5f, 4.9f, 1.8f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 6.0f);

	m_hp = 2;
	m_maxHP = m_hp;
	m_graivty = 0.05f;
	m_scale = 1.8f;
	m_isCollsionTime = false;
	m_collisionTime = 0;

	m_behavior = std::make_unique<BehaviorTree>(m_player, this);
	m_behavior->Initialize(m_commonResources);


	m_acceleration = 0;
	m_knockbackDirection = DirectX::SimpleMath::Vector3::Zero;
	m_knockbackTime = 0;

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Enemy::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();

	m_behavior->Update(elapsedTime);


	if (m_isCollsionTime)
	{

		if (m_knockbackTime < 0.2f)
		{




			//�e����鏈��

			m_acceleration += 90.0f * elapsedTime;

			m_acceleration = std::min(m_acceleration, 60.0f);

			DirectX::SimpleMath::Vector3 Direction = m_knockbackDirection;

			Direction *= m_acceleration * elapsedTime;

			m_position += Direction;

		}


		m_knockbackTime += elapsedTime;

		if (m_knockbackTime >= 5)
		{
			m_isCollsionTime = false;
			m_knockbackTime = 0;
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


	//�v���C���ƓG�̃x�N�g��
	DirectX::SimpleMath::Vector3 vec = m_player->GetPos() - m_position;
	vec.Normalize();
	//�v���C���̕����Ɍ����邽�߂̉�]
	DirectX::SimpleMath::Quaternion Rotate;

	Rotate = DirectX::SimpleMath::Quaternion::FromToRotation(STAETTAEGETDIRECTION, vec);

	DirectX::SimpleMath::Vector3 Pos = DirectX::SimpleMath::Vector3::Transform(STAETTAEGETDIRECTION, Rotate);

	m_targetPos = m_position + Pos;

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




void Enemy::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}

void Enemy::OnCollision(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	//�u�[�������Ɠ������Ƃ��ɖ��t���[��Hp���ւ�Ȃ��悤�ɂ���
	if (m_isCollsionTime)
	{
		return;
	}

	m_hp--;

	m_isCollsionTime = true;

	//�u�[�������Ƃ̍��W����e�����������߂�

//����
	m_knockbackDirection = m_position - Pos;
	m_knockbackDirection.y = 0;

	m_knockbackDirection.Normalize();

	m_acceleration = 0;

}
