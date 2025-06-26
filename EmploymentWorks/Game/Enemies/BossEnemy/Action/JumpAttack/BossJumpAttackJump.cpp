/*
	@file	BossJumpAttackJump.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BossJumpAttackJump.h"
#include "GameBase/Common/Commons.h"
#include "Game/Enemies/BossEnemy/Action/JumpAttack/BossJumpAttackActionController.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Player/Player.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="parent">�R���g���[���[</param>
/// <param name="bossenemy">���L��</param>
/// <param name="player">�v���C��</param>
BossJumpAttackJump::BossJumpAttackJump(BossJumpAttackActionController* controller
	,BossEnemy* bossenemy
	, Player* player)
	:
	m_commonResources{}
	,m_bossEnemy{bossenemy}
	,m_player{player}
	,m_controller{ controller }
	,m_jumpDirection{}
{
	m_commonResources = CommonResources::GetInstance();



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossJumpAttackJump::~BossJumpAttackJump()
{
	// do nothing.
}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�p�����I����</returns>
BossJumpAttackJump::ActionState BossJumpAttackJump::Update(const float& deltaTime)
{

	using namespace DirectX::SimpleMath;
	

	float speed = 5.0f;

	auto rigidbody = m_bossEnemy->GetComponent<RigidbodyComponent>();

	auto velocity = rigidbody->GetVelocity();

	velocity.x = m_jumpDirection.x * speed * deltaTime;
	velocity.z = m_jumpDirection.z * speed * deltaTime;

	rigidbody->SetVelocity(velocity);

	//���n������
	if (m_bossEnemy->GetIsGround())
	{
		auto rigidbody = m_bossEnemy->GetComponent<RigidbodyComponent>();
		rigidbody->SetAddForce(Vector3::Zero);
		rigidbody->SetVelocity(Vector3::Zero);
		return ActionState::END;
	}

	
	m_time = deltaTime;
	return ActionState::RUNNING;

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BossJumpAttackJump::Enter()
{
	using namespace DirectX::SimpleMath;

	auto rigidbody = m_bossEnemy->GetComponent<RigidbodyComponent>();
	//�W�����v�͂̉��Z
	rigidbody->AddForce(Vector3(0, 10, 0));

	m_startPosition = m_bossEnemy->GetTransform()-> GetPosition();

	m_targetPosition = m_player->GetTransform()->GetPosition();


	//���������߂�
	m_jumpDirection = m_targetPosition - m_startPosition;
	m_jumpDirection.y = 0.0f;
	m_jumpDirection.Normalize();

	m_time = 0.0f;




}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BossJumpAttackJump::Exit()
{

	//m_bossEnemy->ChangeAnimation("Idel");

	//Vector3 pos = m_bossEnemy->GetPosition();

	//pos.y = 0.1f;

	//Messenger::GetInstance()->Notify(GamePlayMessageType::CREATE_PARTICLE, &pos);

	//m_bossEnemy->SetVelocity(Vector3::Zero);

}
