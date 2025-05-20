/*
	@file	BossJumpAttackAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Entities/ActionStateController.h"
#include "Game/Interface/IObserver.h"
#include "Game/Enemys/BossEnemy/ActionNode/JumpAttack/BossJumpAttackCharge.h"
#include "Game/Enemys/BossEnemy/ActionNode/JumpAttack/BossJumpAttackJump.h"
#include "Game/Enemys/BossEnemy/ActionNode/Orientation/OrientationAction.h"


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


class BossJumpAttackAction : public ActionStateController 
{

public:

	static  constexpr float JUMPPOWER = 0.3f;

	static  constexpr float MOVESPEED = 9.0f;

public:



	BossJumpAttackCharge* GetBossJumpAttackCharge() { return m_charge.get(); }

	BossJumpAttackJump* GetBossJumpAttackJump() { return m_jump.get(); }


public:
	//�R���X�g���N�^
	BossJumpAttackAction(CommonResources* resources,
		BossEnemy* bossEnemy
		, Player* player);
	//�f�X�g���N�^
	~BossJumpAttackAction();




private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	//�`���[�W
	std::unique_ptr<BossJumpAttackCharge> m_charge;
	//�W�����v
	std::unique_ptr<BossJumpAttackJump> m_jump;


};
