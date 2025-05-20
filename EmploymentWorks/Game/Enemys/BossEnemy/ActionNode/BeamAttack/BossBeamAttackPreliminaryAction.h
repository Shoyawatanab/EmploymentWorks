/*
	@file	BossBeamAttackPreliminaryAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"

// �O���錾
class CommonResources;
class CharacterEntity;
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
	//�R���X�g���N�^
	BossBeamAttackPreliminaryAction(CommonResources* resources
		, CharacterEntity* bossEnemy
		,Beam* beam
		, BossBeamAttackAction* beamAttack);

	
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
	//���L��
	CharacterEntity* m_bossEnemy;
	//�r�[��
	Beam* m_beam;
	//�r�[���U��
	BossBeamAttackAction* m_beamAttack;


};
