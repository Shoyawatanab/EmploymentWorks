/*
	@file	BossBeamAttackPreliminaryAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"

// �O���錾
class CommonResources;
class BossEnemy;
class Beam;
class BossBeamAttackAction;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}



class BossBeamAttackPreliminaryAction : public IAction
{
public:
	BossBeamAttackPreliminaryAction(CommonResources* resources
		,BossEnemy* bossEnemy
		,Beam* beam
		, BossBeamAttackAction* beamAttack);

	//�p���֌W
		//�f�X�g���N�^
	~BossBeamAttackPreliminaryAction() override;
	//������
	void Initialize() override;
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

	BossEnemy* m_bossEnemy;
	Beam* m_beam;
	BossBeamAttackAction* m_beamAttack;


};
