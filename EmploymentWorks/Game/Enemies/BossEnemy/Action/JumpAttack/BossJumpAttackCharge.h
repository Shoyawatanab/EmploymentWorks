/*
	@file	BossJumpAttackCharge.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// �O���錾
class CommonResources;
class Beam;
class BossJumpAttackActionController;




class BossJumpAttackCharge : public IAction
{

public:

	//�G�t�F�N�g�̑傫��
	static constexpr DirectX::SimpleMath::Vector3 EFFECTE_SCALE{ 5.0f,5.0f,5.0f };
	//�`���[�W����
	static constexpr float CHARGE_TIME = 1.5f;

public:
	//�R���X�g���N�^
	BossJumpAttackCharge(BossJumpAttackActionController* controller
		,Actor* bossEnemy
		,Actor* player);
	//�f�X�g���N�^
	~BossJumpAttackCharge() override ;
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
	Actor* m_bossEnemy;
	//�v���C��
	Actor* m_player;
	//����
	float m_time;
	//�R���g���[���[
	BossJumpAttackActionController* m_controller;


};
