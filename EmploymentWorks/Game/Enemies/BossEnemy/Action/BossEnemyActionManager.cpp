#include "pch.h"
#include "BossEnemyActionManager.h"
#include "Game/Enemies/BossEnemy/Action/BossEnemyActions.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
BossEnemyActionManager::BossEnemyActionManager(BossEnemy* ower,Player* target, BossEnemyBeam* beam)
{

	//�e�A�N�V�����̍쐬
	AddAction("Idle",std::make_unique<IdleingActionComtroller>());
	AddAction("JumpAttack",std::make_unique<BossJumpAttackActionController>(ower,target));
	AddAction("Walk",std::make_unique<WalkActionComtroller>(ower,target));
	AddAction("SwingDown",std::make_unique<SwingDownAttackActionController>(ower));
	AddAction("Beam",std::make_unique<BossBeamAttackActionController>(ower,beam,target));
	AddAction("Orientation", std::make_unique<OrientationActionController>(ower, target));
	AddAction("Orientation", std::make_unique<OrientationActionController>(ower, target));
	AddAction("Death", std::make_unique<BossDeathActionComtroller>(ower));

	SetStartAction("Idle");
	

	//���b�Z�[�W�̓o�^
	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::BOSS_IDLE_STATE
			,SceneMessageType::BOSS_BEAM_ATTACK_STATE
			,SceneMessageType::BOSS_JUMP_ATTACK_STATE
			,SceneMessageType::BOSS_SWING_DOWN_STATE
			,SceneMessageType::BOSS_WAKING_STATE
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
void BossEnemyActionManager::Notify(SceneMessageType type, void* datas)
{
	switch (type)
	{
		case SceneMessageType::BOSS_IDLE_STATE:
			ChangeAction("Idle");
			break;
		case SceneMessageType::BOSS_BEAM_ATTACK_STATE:
			ChangeAction("Beam");
			break;
		case SceneMessageType::BOSS_JUMP_ATTACK_STATE:
			ChangeAction("JumpAttack");
			break;
		case SceneMessageType::BOSS_WAKING_STATE:
			ChangeAction("Walk");
			break;
		case SceneMessageType::BOSS_SWING_DOWN_STATE:
			ChangeAction("SwingDown");
			break;

		default:
			break;
	}
}
