/*
	@file	BossJumpAttackJump.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"

// �O���錾
class CommonResources;
class BossEnemy;
class Beam;
class Player;
class BossJumpAttackAction;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossJumpAttackJump : public IAction
{


public:
	BossJumpAttackJump(CommonResources* resources,
		BossJumpAttackAction* parent
		,BossEnemy* bossEnemy
		, Player* player);
	//�f�X�g���N�^
	~BossJumpAttackJump() override ;

	void Initialize() override;

	IBehaviorNode::State Update(const float& elapsedTime)  override ;
	//��Ԃɓ�������
	void Enter() override ;
	//��Ԃ𔲂�����
	void Exit() override;

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	BossEnemy* m_bossEnemy;
	Player* m_player;
	BossJumpAttackAction* m_parent;


	DirectX::SimpleMath::Vector3 m_jumpDirection;


};
