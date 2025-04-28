/*
	@file	BossBeamAttackAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "Game/Interface/IObserver.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackIdel.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackPreliminaryAction.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackCharge.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackShot.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackEnd.h"

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


class BossBeamAttackAction : public IAction , IObserver
{

public:


	BossBeamAttackPreliminaryAction* GetBossBeamAttackPreliminaryAction() { return m_preliminaryAction.get(); }

	BossBeamAttackCharge* GetBossBeamAttackCharge() { return m_charge.get(); }

	BossBeamAttackShot* GetBossBeamAttackShot() { return m_shot.get(); }

	BossBeamAttackEnd* GetBossBeamAttackEnd() { return m_attackEnd.get(); }

	BossBeamAttackIdel* GetBossBeamAttackIdel() { return m_idel.get(); }

	IAction* GetCurrentState() { return m_currentState; }


public:
	BossBeamAttackAction(CommonResources* resources,
		BossEnemy* bossEnemy
		, Beam* beam
		, Player* player);
	//�f�X�g���N�^
	~BossBeamAttackAction() override ;

	void Initialize() override;

	ActionState Update(const float& elapsedTime)  override ;

	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;


	//IObserver
//�ʒm���ɌĂ΂��֐�
	void Notify(const Telegram& telegram)  override;

	//��Ԃ̕ύX
	void ChangeState(IAction* nextState);


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	IAction* m_currentState;

	std::unique_ptr<BossBeamAttackPreliminaryAction> m_preliminaryAction;

	std::unique_ptr<BossBeamAttackCharge> m_charge;

	std::unique_ptr<BossBeamAttackShot> m_shot;

	std::unique_ptr<BossBeamAttackEnd> m_attackEnd;

	std::unique_ptr<BossBeamAttackIdel> m_idel;
};
