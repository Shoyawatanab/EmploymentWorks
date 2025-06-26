#include "pch.h"
#include "BirdEnemyBulletShot.h"
#include <random>
#include "Game/Params.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Enemies/BirdEnemy/Bullet/BirdEnemyBullet.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BirdEnemy/BirdEnemy.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStateMachine.h"
#include "Game/MathUtil.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="stateMachine">�X�e�[�g�}�V��</param>
/// <param name="birdEnemy">���G</param>
BirdEnemyBulletShot::BirdEnemyBulletShot(BirdEnemyBulletStateMachine* stateMachine, BirdEnemyBullet* bullet, BirdEnemy* birdEnemy)
	:
	m_stateMahine{ stateMachine }
	,m_bullet{ bullet }
	,m_birdEnemy{birdEnemy}
	,m_time{}
	,m_moveDirection{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyBulletShot::~BirdEnemyBulletShot()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void BirdEnemyBulletShot::Update(const float& deltaTime)
{
	//��Ԃ̂��߂̎��Ԃ����߂�@�@�o�ߎ��Ԃ��������ԂɂȂ�܂ł͂O�`�P�̊ԁ@�o�ߎ��Ԃ��������Ԃ𒴂���ƂP
	float t = std::min(m_time, Params::BIRDENEMY_BEAM_BALL_DECELERATION_TIME) / Params::BIRDENEMY_BEAM_BALL_DECELERATION_TIME;
	//�����ƏI���ŕ�Ԃ��Ĉړ����x�����߂�
	float moveSpeed = MathUtil::Lerp(Params::BIRDENEMY_BEAM_BALL_INITIAL_SPEED, Params::BIRDENEMY_BEAM_BALL_FAINAL_SPEED, t);


	//auto rigidbody = m_bullet->GetComponent<RigidbodyComponent>();
	//rigidbody->SetVelocity(m_moveDirection * moveSpeed);

	m_bullet->GetTransform()->SetPosition(m_bullet->GetTransform()->GetWorldPosition() + (m_moveDirection * moveSpeed * deltaTime));

	m_time += deltaTime;
}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BirdEnemyBulletShot::Enter()
{


	//���˕������v�Z
	m_moveDirection = m_birdEnemy->GetTarget()->GetTransform()->GetRotatePosition() - m_bullet->GetTransform()->GetRotatePosition() ;
	//m_moveDirection.Normalize();
	m_time = 0.0f;

	m_bullet->GetTransform()->SetParent(nullptr);
	//���L�҂̏�Ԃ�ύX
	m_birdEnemy->GetStateMachine()->ChangeState(BirdEnemyState::IDEL);

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BirdEnemyBulletShot::Exit()
{
}
