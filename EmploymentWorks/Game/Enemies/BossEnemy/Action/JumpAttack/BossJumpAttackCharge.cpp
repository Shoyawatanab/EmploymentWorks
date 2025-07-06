#include "pch.h"
#include "BossJumpAttackCharge.h"
#include "GameBase/Common/Commons.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Component/Components.h"
#include "Game/Enemies/BossEnemy/Action/JumpAttack/BossJumpAttackActionController.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
BossJumpAttackCharge::BossJumpAttackCharge(BossJumpAttackActionController* controller
	,Actor* bossenemy
	, Actor* player)
	:
	m_commonResources{}
	,m_bossEnemy{bossenemy}
	,m_player{player}
	,m_controller{ controller }
	,m_time{}
{
	m_commonResources = CommonResources::GetInstance();

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossJumpAttackCharge::~BossJumpAttackCharge()
{
	// do nothing.
}


BossJumpAttackCharge::ActionState BossJumpAttackCharge::Update(const float& elapsedTime)
{
	//���Ԃ̓A�j���[�V�����ƍ��킹��
	if (m_time >= CHARGE_TIME)
	{
		return ActionState::END;
	}

	
	m_time += elapsedTime;

	return ActionState::RUNNING;

}


void BossJumpAttackCharge::Enter()
{

	m_time = 0;

	auto  startPosition = m_bossEnemy->GetTransform()->GetPosition();

	auto targetPosition = m_player->GetTransform()->GetPosition();

	auto jumpDirection = targetPosition - startPosition;

	m_controller->SetJumpDirection(jumpDirection);

	CreateChargeEffectDatas datas;
	datas.Position = m_bossEnemy->GetTransform()->GetWorldPosition();
	datas.Scale = m_bossEnemy->GetTransform()->GetWorldScale();

	datas.Position.y = 0.1f;

	//�G�t�F�N�g�쐬�̒ʒm
	SceneMessenger::GetInstance()->Notify(SceneMessageType::CREATE_CHARGE_EFFECT, &datas);
	//�W�����v�A�j���[�V�����̒ʒm
	SceneMessenger::GetInstance()->Notify(SceneMessageType::BOSS_JUMP_ANIMATION_START);

}

void BossJumpAttackCharge::Exit()
{
}
