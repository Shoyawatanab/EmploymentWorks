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
#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/Beam.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyBottom.h"


//�����̃^�[�Q�b�g�̍��W�̋���
const DirectX::SimpleMath::Vector3 Enemy::STAETTAEGETDIRECTION = DirectX::SimpleMath::Vector3(0, 0, 2.5f);

//�G�̏����̌����Ă������
const DirectX::SimpleMath::Vector3 Enemy::INITIALFORWARD = DirectX::SimpleMath::Vector3(0, 0, 1);

const int MAXHP = 1;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Enemy::Enemy(CommonResources* resources, IComponent* parent, const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BossEnemyBase(resources, parent, initialScale, DirectX::SimpleMath::Vector3::Zero, initialAngle),
	m_commonResources{resources},
	//m_model{},
	m_position{initialPosition},
	m_hp{},
	m_behavior{},
	m_player{},
	m_knockbackDirection{},
	m_targetPos{},
	m_forward{ INITIALFORWARD }
	,m_acceleration{}
	,m_collisionTime{}
	,m_graivty{}
	,m_isAttack{}
	,m_isCollsionTime{}
	,m_knockbackTime{}
	,m_maxHP{}
	,m_onCollisionTag{}
	,m_scale{}
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
void Enemy::Initialize()
{
	using namespace DirectX::SimpleMath;



	//m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();




	//// ���f����ǂݍ��ޏ���
	//std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	//fx->SetDirectory(L"Resources/Models");

	//// ���f����ǂݍ���
	//m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemy.cmo", *fx);

	//m_position = initialPosition;

	m_initialRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, DirectX::XMConvertToRadians(90.0f));
	m_rotate = DirectX::SimpleMath::Quaternion::Identity;


	m_bounding->CreateBoundingBox(m_commonResources, m_position + Vector3(0,1,0), Vector3(4.5f, 5.5f, 1.8f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 6.0f);

	m_hp = MAXHP;
	m_maxHP = m_hp;
	m_graivty = 0.05f;
	//m_scale = 1.8f / 100;
	m_scale = Vector3(1.5f, 1.5f, 1.5f);
	m_isCollsionTime = false;
	m_collisionTime = 0;

	m_behavior->Initialize(m_commonResources);


	m_acceleration = 0;
	m_knockbackDirection = DirectX::SimpleMath::Vector3::Zero;
	m_knockbackTime = 0;

	m_beam->Initialize(m_commonResources, m_player, this);

	m_onCollisionTag = CollsionObjectTag::None;

	//�uBottom�v�𐶐�����
	Attach(std::make_unique<BossEnemyBottom>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(0.0f, -0.6f, 0.0f), Quaternion::Identity));

	RegistrationRungingAnimation("Beam");

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

	BossEnemyBase::AnimationUdate(elapsedTime);


	//���i���X�V����
	BossEnemyBase::Update(elapsedTime);


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


	m_position.y -= m_graivty;


	//�v���C���ƓG�̃x�N�g��
	DirectX::SimpleMath::Vector3 vec = m_player->GetPos() - m_position;
	vec.Normalize();
	//�v���C���̕����Ɍ����邽�߂̉�]
	DirectX::SimpleMath::Quaternion Rotate;

	Rotate = DirectX::SimpleMath::Quaternion::FromToRotation(STAETTAEGETDIRECTION, vec);

	DirectX::SimpleMath::Vector3 Pos = DirectX::SimpleMath::Vector3::Transform(STAETTAEGETDIRECTION, Rotate);

	m_targetPos = m_position + Pos;

	m_bounding->Update(m_position + DirectX::SimpleMath::Vector3(0,1,0));

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Enemy::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	// ���[���h�s����X�V����
	m_worldMatrix = Matrix::CreateScale(m_scale);
	//�̂��ɕύX����@�����p�x�������ł��Ȃ��ƃv���C���̕����Ɍ��������ɉe�����o�Č����Ȃ��Ȃ�
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_initialRotate);

	m_worldMatrix *= Matrix::CreateFromQuaternion(m_rotate);
	m_worldMatrix *= Matrix::CreateTranslation(m_position);

	//���i��`�悷��
	BossEnemyBase::Render(view, projection);

	// ���f����`�悷��
	//m_model->Draw(context, *states, world, view, projection);

	m_bounding->DrawBoundingBox(view, projection);
	m_bounding->DrawBoundingSphere(view, projection);

	m_beam->Render(view, projection);


}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Enemy::Finalize()
{
	// do nothing.
}

//�傫��������������
void Enemy::ReduceSize(float elapsdTime)
{

	UNREFERENCED_PARAMETER(elapsdTime);

	//m_scale -= 0.01f;
	//m_scale = std::max(m_scale, 0.0f);
}

void Enemy::RegistrationInformation( Player* player)
{

	m_player = player;
	
	m_behavior->RegistrationInformation(m_player, this);

}


void Enemy::Instances()
{

	m_bounding = std::make_unique<Bounding>();
	m_behavior = std::make_unique<BehaviorTree>();
	m_beam = std::make_unique<Beam>();


}




void Enemy::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);

	BossEnemyBase::RegistrationCollionManager(collsionManager);
}



IBehaviorNode::State Enemy::BeamAttack(float elapsdTime)
{

	if (m_beam->Attack(elapsdTime))
	{
		m_isAttack = true;
		//�U����
		return IBehaviorNode::State::Runngin;
	}

	m_isAttack = false;

	//�U���I��
	return IBehaviorNode::State::Success;

}


void Enemy::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	//�����땔�W�F�N�g�̃^�O��
	switch (PartnerTag)
	{
		case CollsionObjectTag::Boomerang:
			//�u�[�������Ɠ������Ƃ��ɖ��t���[��Hp���ւ�Ȃ��悤�ɂ���
			if (m_isCollsionTime)
			{
				return;
			}

			m_hp--;

			m_isCollsionTime = true;
			break;
		case CollsionObjectTag::ArtilleryBullet:
			
			m_hp -= 2;

			break;
		default:
			break;
	}

	//�u�[�������Ƃ̍��W����e�����������߂�

//����
	m_knockbackDirection = m_position - Pos;
	m_knockbackDirection.y = 0;

	m_knockbackDirection.Normalize();

	m_acceleration = 0;

}
