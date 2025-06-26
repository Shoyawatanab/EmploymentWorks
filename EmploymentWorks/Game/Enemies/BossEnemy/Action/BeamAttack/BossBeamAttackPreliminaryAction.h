/*
	@file	BossBeamAttackPreliminaryAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// �O���錾
class CommonResources;
class BossEnemyBeam;
class BossBeamAttackActionController;





class BossBeamAttackPreliminaryAction : public IAction
{
public:
	//�R���X�g���N�^
	BossBeamAttackPreliminaryAction(Actor* bossEnemy
		, BossEnemyBeam* beam
		, BossBeamAttackActionController* beamAttack);

	
	//�f�X�g���N�^
	~BossBeamAttackPreliminaryAction() override;
	// �X�V����
	ActionState Update(const float& elapsedTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override ;
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	//�o�ߎ���
	float m_time;
	//���L��
	Actor* m_bossEnemy;
	//�r�[��
	BossEnemyBeam* m_beam;
	//�r�[���U��
	BossBeamAttackActionController* m_beamAttack;


};
