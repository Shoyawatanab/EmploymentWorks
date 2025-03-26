/*
	@file	BossJumpAttackAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"
#include"Game/Interface/IActionState.h"
#include "Game/Interface/IObserver.h"
#include "Game/Enemys/BossEnemy/ActionNode/JumpAttack/BossJumpAttackCharge.h"
#include "Game/Enemys/BossEnemy/ActionNode/JumpAttack/BossJumpAttackJump.h"

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


class BossJumpAttackAction : public IAction , IObserver
{

public:


	IAction* GetCurrentState() { return m_currentState; }

	BossJumpAttackCharge* GetBossJumpAttackCharge() { return m_charge.get(); }

	BossJumpAttackJump* GetBossJumpAttackJump() { return m_jump.get(); }

public:
	BossJumpAttackAction(CommonResources* resources,
		BossEnemy* bossEnemy
		, Player* player);
	//�f�X�g���N�^
	~BossJumpAttackAction() override ;

	void Initialize() override;

	IBehaviorNode::State Update(const float& elapsedTime)  override ;
	//��Ԃɓ�������
	void Enter() override ;
	//��Ԃ𔲂�����
	void Exit() override;


	//IObserver
//�ʒm���ɌĂ΂��֐�
	void Notify(EventParams::EventType type, void* datas)  override;

	//��Ԃ̕ύX
	void ChangeState(IAction* nextState);


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	IAction* m_currentState;

	std::unique_ptr<BossJumpAttackCharge> m_charge;

	std::unique_ptr<BossJumpAttackJump> m_jump;

};
