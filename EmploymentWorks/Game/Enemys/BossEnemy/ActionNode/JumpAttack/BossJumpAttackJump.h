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
	//�R���X�g���N�^
	BossJumpAttackJump(CommonResources* resources,
		BossJumpAttackAction* parent
		,BossEnemy* bossEnemy
		, Player* player);
	//�f�X�g���N�^
	~BossJumpAttackJump() override ;
	//������
	void Initialize() override;
	//�X�V����
	ActionState Update(const float& elapsedTime)  override ;
	//��Ԃɓ�������
	void Enter() override ;
	//��Ԃ𔲂�����
	void Exit() override;

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//���L��
	BossEnemy* m_bossEnemy;
	//�v���C��
	Player* m_player;
	//�R���g���[���[
	BossJumpAttackAction* m_parent;
	//�W�����v����
	DirectX::SimpleMath::Vector3 m_jumpDirection;


};
