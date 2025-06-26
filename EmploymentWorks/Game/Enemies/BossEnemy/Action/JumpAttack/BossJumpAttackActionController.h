/*
	@file	BossJumpAttackActionController.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "GameBase/Action/ActionController.h"
#include "GameBase/Actor.h"

#include "Game/Enemies/BossEnemy/Action/JumpAttack/BossJumpAttackCharge.h"
#include "Game/Enemies/BossEnemy/Action/JumpAttack/BossJumpAttackJump.h"
#include "Game/Enemies/BossEnemy/Action/Orientation/OrientationAction.h"


// �O���錾
class CommonResources;
class Player;
class BossEnemy;



class BossJumpAttackActionController : public ActionController 
{

public:
	//�W�����v��
	static  constexpr float JUMPPOWER = 0.3f;
	//�����̃X�s�[�h
	static  constexpr float MOVESPEED = 9.0f;

public:
	//�R���X�g���N�^
	BossJumpAttackActionController(BossEnemy* bossEnemy
		, Player* player);
	//�f�X�g���N�^
	~BossJumpAttackActionController()override;




private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	//�`���[�W
	std::unique_ptr<BossJumpAttackCharge> m_charge;
	//�W�����v
	std::unique_ptr<BossJumpAttackJump> m_jump;
	//��]
	std::unique_ptr<OrientationAction> m_orientation;


};
