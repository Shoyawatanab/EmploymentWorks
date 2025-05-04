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


class BossRushAttackAction : public ActionStateController, IObserver
{

public:



public:
	BossRushAttackAction(CommonResources* resources,
		BossEnemy* bossEnemy
		, Player* player);
	//�f�X�g���N�^
	~BossRushAttackAction() ;


	//IObserver
//�ʒm���ɌĂ΂��֐�
	void Notify(const Telegram& telegram)  override;



private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	std::unique_ptr<BossRushAttackCharge> m_charge;

	std::unique_ptr<BossRushAttackRush> m_rush;

};
