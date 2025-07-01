/*
	@file	BossBeamAttackCharge.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// �O���錾
class CommonResources;
class BossEnemyBeam;
class BossBeamAttackActionController;
class BossEnemy;




class BossBeamAttackCharge : public IAction
{
public:
	//�R���X�g���N�^
	BossBeamAttackCharge(BossEnemy* bossEnemy
		, BossEnemyBeam* beam
		, BossBeamAttackActionController* beamAttack);


	//�f�X�g���N�^
	~BossBeamAttackCharge() override;
	// �X�V����
	ActionState Update(const float& elapsedTime) override;

	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�{�X�e�L
	BossEnemy* m_bossEnemy;
	//�r�[��
	BossEnemyBeam* m_beam;
	//����
	float m_time;
	//�p�[�e�B�N����������
	float m_particleCreateTime;


};
