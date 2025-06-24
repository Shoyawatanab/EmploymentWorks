#include "pch.h"
#include "BossEnemyActionManager.h"
#include "Game/Enemies/BossEnemy/Action/BossEnemyActions.h"
#include "Game/Messenger/Messenger.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
BossEnemyActionManager::BossEnemyActionManager(BossEnemy* ower,Player* target)
{

	//�e�A�N�V�����̍쐬
	AddAction("Idle",std::make_unique<IdleingActionComtroller>());
	AddAction("JumpAttack",std::make_unique<BossJumpAttackActionController>(ower,target));
	AddAction("Walk",std::make_unique<WalkActionComtroller>(ower,target));
	AddAction("SwingDown",std::make_unique<SwingDownAttackActionController>(ower));
	//AddAction("Beam",std::make_unique<BossBeamAttackActionController>(ower,target));
	AddAction("Orientation", std::make_unique<OrientationActionController>(ower, target));

	SetStartAction("Idle");
	

	//���b�Z�[�W�̓o�^
	Messenger::GetInstance()->Rigister(
		{
			MessageType::BOSS_IDLE_STATE
			,MessageType::BOSS_BEAM_ATTACK_STATE
			,MessageType::BOSS_JUMP_ATTACK_STATE
			,MessageType::BOSS_SWING_DOWN_STATE
			,MessageType::BOSS_WAKING_STATE
		}
		, this
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemyActionManager::~BossEnemyActionManager()
{
}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void BossEnemyActionManager::Notify(MessageType type, void* datas)
{
	switch (type)
	{
		case MessageType::BOSS_IDLE_STATE:
			ChangeAction("Idle");
			break;
		case MessageType::BOSS_BEAM_ATTACK_STATE:
			ChangeAction("Beam");
			break;
		case MessageType::BOSS_JUMP_ATTACK_STATE:
			ChangeAction("JumpAttack");
			break;
		case MessageType::BOSS_WAKING_STATE:
			ChangeAction("Walk");
			break;
		case MessageType::BOSS_SWING_DOWN_STATE:
			ChangeAction("SwingDown");
			break;

		default:
			break;
	}
}
