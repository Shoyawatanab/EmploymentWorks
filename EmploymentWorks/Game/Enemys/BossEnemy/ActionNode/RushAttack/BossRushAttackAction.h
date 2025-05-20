/*
	@file	BossRushAttackAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Entities/ActionStateController.h"
#include "Game/Interface/IObserver.h"
#include "Game/Enemys/BossEnemy/ActionNode/RushAttack/BossRushAttackCharge.h"
#include "Game/Enemys/BossEnemy/ActionNode/RushAttack/BossRushAttackRush.h"

// �O���錾
class CommonResources;
class BossEnemy;
class Beam;
class Player;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossRushAttackAction : public ActionStateController
{


public:
	//�R���X�g���N�^
	BossRushAttackAction(CommonResources* resources,
		BossEnemy* bossEnemy
		, Player* player);
	//�f�X�g���N�^
	~BossRushAttackAction() ;





private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�`���[�W
	std::unique_ptr<BossRushAttackCharge> m_charge;
	//���b�V��
	std::unique_ptr<BossRushAttackRush> m_rush;

};
