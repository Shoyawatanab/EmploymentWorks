/*
	@file	BossJumpAttackJump.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// �O���錾
class CommonResources;
class BossJumpAttackActionController;
class Player;
class BossEnemy;


class BossJumpAttackJump : public IAction
{


public:
	//�R���X�g���N�^
	BossJumpAttackJump(BossJumpAttackActionController* controller
		,BossEnemy* bossEnemy
		, Player* player);
	//�f�X�g���N�^
	~BossJumpAttackJump() override ;
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
	BossJumpAttackActionController* m_controller;
	//�W�����v����
	DirectX::SimpleMath::Vector3 m_jumpDirection;
	//
	DirectX::SimpleMath::Vector3 m_startPosition;
	//
	DirectX::SimpleMath::Vector3 m_targetPosition;

	float m_time;

};
