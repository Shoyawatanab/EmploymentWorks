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

const int MAXHP = 10;

//�r�[���U���̗\�����쎞��
const float BEAMATTACKPRELIMINRRYACTIONTIME = 2.0f;

const float WALKMAXSPEED = 2.0f;

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

	//auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();




	//// ���f����ǂݍ��ޏ���
	//std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	//fx->SetDirectory(L"Resources/Models");

	//// ���f����ǂݍ���
	//m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemy.cmo", *fx);

	//m_position = initialPosition;

	m_initialRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, DirectX::XMConvertToRadians(90.0f));
	m_rotate = DirectX::SimpleMath::Quaternion::Identity;

	//m_rotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180.0f));

	m_boundingBoxCenter = Vector3(0, 1, 0);

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position + m_boundingBoxCenter, Vector3(4.5f, 5.5f, 1.8f));
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

	m_rightHandPos = m_position + Vector3(-1.5f,-3, 7.50);

	m_beamStartPosition = Vector3::Transform(m_rightHandPos, m_rotate);

	//m_hp = 7;
	//�U���̗\�����쎞�Ԃ̏�����
	m_preliminaryActionTime = 0;

	//Walk�֌W�̕ϐ��̏�����
	m_walkSpeed = 0.0f;
	m_walkAccelration = 5.0f;
	m_stepDuration = 0.5f;
	m_stepTime = 0.0f;
	m_isStep = true;

	//JumpAttack
	m_jumpHeight = 3.0f;
	m_jumpAttackTime = 0;
	m_transformRatio = 0;

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Enemy::Update(float elapsedTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsedTime);


	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	//�f�o�b�N�p
	if (kbTracker->released.Q)
	{
		m_hp = 1;
	}


	m_behavior->Update(elapsedTime);


	//���i���X�V����
	BossEnemyBase::Update(elapsedTime);

	BossEnemyBase::AnimationUdate(elapsedTime);



	//m_rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.1f))
	//�r�[���̊J�n�n�_�����߂�
	m_beamStartPosition = Vector3::Transform(m_rightHandPos, m_rotate) + m_position;

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
	DirectX::SimpleMath::Vector3 vec = m_player->GetPosition() - m_position;
	vec.Normalize();
	//�v���C���̕����Ɍ����邽�߂̉�]
	DirectX::SimpleMath::Quaternion Rotate;

	Rotate = DirectX::SimpleMath::Quaternion::FromToRotation(STAETTAEGETDIRECTION, vec);

	DirectX::SimpleMath::Vector3 Pos = DirectX::SimpleMath::Vector3::Transform(STAETTAEGETDIRECTION, Rotate);

	m_targetPos = m_position + Pos;

	m_bounding->Update(m_position + m_boundingBoxCenter);

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Enemy::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace DirectX::SimpleMath;

	//auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	//auto states = m_commonResources->GetCommonStates();


	//// ���[���h�s����X�V����
	//m_worldMatrix = Matrix::CreateScale(m_scale);
	////�̂��ɕύX����@�����p�x�������ł��Ȃ��ƃv���C���̕����Ɍ��������ɉe�����o�Č����Ȃ��Ȃ�
	//m_worldMatrix *= Matrix::CreateFromQuaternion(m_initialRotate);

	//m_worldMatrix *= Matrix::CreateFromQuaternion(m_rotate);
	//m_worldMatrix *= Matrix::CreateTranslation(m_position);

	//���i��`�悷��
	BossEnemyBase::Render(view, projection);

	// ���f����`�悷��
	//m_model->Draw(context, *states, world, view, projection);

	m_bounding->DrawBoundingBox(view, projection);
	m_bounding->DrawBoundingSphere(view, projection);

	if (m_hp > 0)
	{
		m_beam->Render(view, projection);

	}


}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Enemy::Finalize()
{
	// do nothing.
}

//�傫��������������
Animation::AnimationState  Enemy::FallDwonAnimation(float elapsdTime)
{

	UNREFERENCED_PARAMETER(elapsdTime);

	Animation::AnimationState state;

	state = BossEnemyBase::AnimationUdate(elapsdTime);


	//���i���X�V����
	BossEnemyBase::Update(elapsdTime);






	if (state == Animation::AnimationState::Running)
	{
		m_position.y += 2.0f *elapsdTime;

		DirectX::SimpleMath::Vector3 velocity = m_forward *  0.5f * elapsdTime;

		

		m_position += velocity;
		

		m_boundingBoxCenter.y += 0.95f * elapsdTime;
	}

	m_position.y -= m_graivty;


	//�v���C���ƓG�̃x�N�g��
	DirectX::SimpleMath::Vector3 vec = m_player->GetPosition() - m_position;
	vec.Normalize();
	//�v���C���̕����Ɍ����邽�߂̉�]
	DirectX::SimpleMath::Quaternion Rotate;

	Rotate = DirectX::SimpleMath::Quaternion::FromToRotation(STAETTAEGETDIRECTION, vec);

	DirectX::SimpleMath::Vector3 Pos = DirectX::SimpleMath::Vector3::Transform(STAETTAEGETDIRECTION, Rotate);

	m_targetPos = m_position + Pos;

	m_bounding->Update(m_position + m_boundingBoxCenter);

	return state;

}

void Enemy::SetAnimation(std::string name)
{

	//RegistrationRungingAnimation("FallDown");

	SetRunnginAnimationName("FallDown");

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

//�����̊֐�
void Enemy::Walk(float elapsdTime)
{

	//�v���C���̍��W�̎擾
	DirectX::SimpleMath::Vector3 playerPosition = m_player->GetPosition();

	//���������߂�
	DirectX::SimpleMath::Vector3 direction = playerPosition - m_position;

	//���K��
	direction.Normalize();

	//
	if (m_isStep)
	{

		m_walkSpeed += m_walkAccelration * elapsdTime;

		m_walkSpeed = std::min(m_walkSpeed, WALKMAXSPEED);

		direction *= m_walkSpeed * elapsdTime;

		m_position += direction;

		m_stepTime += elapsdTime;

		//1�����I��������
		if (m_stepTime >= m_stepDuration)
		{
			m_isStep = false;
			m_walkSpeed = 0.0f;
			m_stepTime = 0.0f;
		}

	}
	else if(!m_isStep)
	{

		m_stepTime += elapsdTime;

		if (m_stepTime >= m_stepDuration)
		{
			m_isStep = true;
			m_stepTime = 0.0f;
		}

	}
}

/// <summary>
/// �W�����v���ē��݂���U��
/// </summary>
/// <param name="elapstTime"></param>
IBehaviorNode::State Enemy::JumpAttack(float elapstTime)
{
	using namespace DirectX::SimpleMath;

	//���߂̂P�񂾂��Ăт���
	if (!m_isAttack)
	{
		m_jumpHeight = 2.0f;
		m_isAttack = true;
		//�v���C���̍��W�������l��
		m_jumpPosition.push_back(m_position);
		//���ԍ��W�����߂�
		DirectX::SimpleMath::Vector3 middlePosition = (m_player->GetPosition() - m_position) / 2;
		middlePosition += m_position;
		//�������w�肵�����̂ɕύX����
		middlePosition.y = m_jumpHeight + m_position.y;
		//���ԍ��W��o�^
		m_jumpPosition.push_back(middlePosition );

		DirectX::SimpleMath::Vector3 targetPosition = m_player->GetPosition();
		targetPosition.y = m_position.y;
		//�ŏI���W��o�^
		m_jumpPosition.push_back(targetPosition);
		//���Ԓn�_�̂����W�𔽓]������
		middlePosition.y *= -1;
		//�S�ڂ̍��W��o�^
		m_jumpPosition.push_back(middlePosition);

		m_jumpAttackIndex =static_cast<int>( m_jumpPosition.size() - 1);

	}

	//�\������
	if (m_preliminaryActionTime < 2)
	{

		m_preliminaryActionTime += elapstTime;

		return IBehaviorNode::State::Runngin;

	}


	//���������߂�
	float distance = (m_jumpPosition[(m_jumpAttackIndex + 2) % m_jumpPosition.size()] -
		m_jumpPosition[(m_jumpAttackIndex + 1) % m_jumpPosition.size()]).Length();
	//�ړ�����
	m_transformRatio = m_jumpAttackTime * 5.0f / distance;

	m_transformRatio = std::min(m_transformRatio, 1.0f);

	DirectX::SimpleMath::Vector3  Pos = Vector3::CatmullRom(
		m_jumpPosition[(m_jumpAttackIndex + 0) % m_jumpPosition.size()],
		m_jumpPosition[(m_jumpAttackIndex + 1) % m_jumpPosition.size()],
		m_jumpPosition[(m_jumpAttackIndex + 2) % m_jumpPosition.size()],
		m_jumpPosition[(m_jumpAttackIndex + 3) % m_jumpPosition.size()],
		m_transformRatio
	);

	m_position = Pos;

	//�������P�𒴂����玟�̓_�Ɉړ�
	if (m_transformRatio >= 1.0f)
	{
		m_jumpAttackIndex++;
		m_jumpAttackTime = 0.0f;
	}

	//�Ō�̓_�ɂ�����v���C����ǂ������鏈���ɐ؂�ւ���
	if (m_jumpAttackIndex >= m_jumpPosition.size() + 1)
	{

		m_jumpPosition.clear();
		m_isAttack = false;
		m_preliminaryActionTime = 0;
		m_jumpAttackTime = 0;


		Vector3 playerPosition = m_player->GetPosition();
		Vector3 enemyPosition = m_position;

		//�������l�����Ȃ�����
		playerPosition.y = 0;
		enemyPosition.y = 0;

		//�_���[�W�͈͓����ǂ���
		float distance = Vector3::Distance(enemyPosition,playerPosition);

		if (distance <= 2)
		{
			int hp = m_player->GetPlayerHP();
			hp -= 1;
			m_player->SetPlayerHP(hp);
		}


		return IBehaviorNode::State::Success;

	}

	m_jumpAttackTime += elapstTime;

	//�U����
	return IBehaviorNode::State::Runngin;
}




void Enemy::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);

	BossEnemyBase::RegistrationCollionManager(collsionManager);
}



IBehaviorNode::State Enemy::BeamAttack(float elapsdTime)
{
	//�U���̏��߂�1�񂾂��\����
	if (m_preliminaryActionTime == 0)
	{
		//�A�j���[�V�����̓o�^
		SetRunnginAnimationName("Beam");
	}


	//�\�����쎞�ԂȂ����ǂ���
	if (m_preliminaryActionTime < BEAMATTACKPRELIMINRRYACTIONTIME)
	{
		//�\�����쎞�Ԃ̉��Z
		m_preliminaryActionTime += elapsdTime;
		FacingThePlayer(elapsdTime);
		//�U����
		return IBehaviorNode::State::Runngin;
	}


	if (m_beam->Attack(elapsdTime))
	{
		m_isAttack = true;
		//�U����
		return IBehaviorNode::State::Runngin;
	}
	//�U�����ǂ����̏�����
	m_isAttack = false;

	//�U���̗\�����쎞�Ԃ̏�����
	m_preliminaryActionTime = 0;

	//�U���I��
	return IBehaviorNode::State::Success;

}

/// <summary>
/// �ߋ����U���@�r�w�C�r�A�c���[�Ȃ��ŌĂяo��
/// </summary>
/// <returns></returns>
IBehaviorNode::State Enemy::CloseRangeAttack(float elapsdTime)
{



	return JumpAttack(elapsdTime);
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

void Enemy::FacingThePlayer(float elapsdTime)
{

	//������������
	DirectX::SimpleMath::Vector3 direction = m_player->GetPosition() - m_position;
	direction.Normalize();
	//���̓G�̑O����
	DirectX::SimpleMath::Vector3 forward = m_forward;
	//forward.Normalize();

	DirectX::SimpleMath::Vector3 moveAxis = forward.Cross(direction);

	if (moveAxis.y >= 0.0f)
	{
		moveAxis = DirectX::SimpleMath::Vector3::Up;
	}
	else
	{
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//�p�x�����߂�
	float moveAngle = forward.Dot(direction);

	//if (moveAngle < 0.01f)
	//{
	//	return IBehaviorNode::State::Failure;
	//}

//���W�A���l�ɕϊ�
	moveAngle = acosf(moveAngle);

	//�p�x�Ƒ��x�̔�r�ŏ������ق����擾
	moveAngle = std::min(moveAngle, 1.0f * elapsdTime);

	//�G�̉�]�̎擾
	DirectX::SimpleMath::Quaternion Rotate = m_rotate;
	//Y���ɑ΂��ĉ�]��������
	Rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	m_rotate = Rotate;

	//��]�����ƂɓG�̏����̕����x�N�g���̍X�V
	forward = DirectX::SimpleMath::Vector3::Transform(Enemy::INITIALFORWARD, Rotate);
	forward.Normalize();
	m_forward = forward;


}
