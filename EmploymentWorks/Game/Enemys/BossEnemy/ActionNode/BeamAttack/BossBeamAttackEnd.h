/*
	@file	BossBeamAttackEnd.h
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


class BossBeamAttackEnd : public IAction
{

public:
	//�R���X�g���N�^
	BossBeamAttackEnd(CommonResources* resources
		, CharacterEntity* bossEnemy
		, Beam* beam
		, BossBeamAttackAction* beamAttack);


	//�f�X�g���N�^
	~BossBeamAttackEnd() override ;
	//������
	void Initialize() override ;
	// �X�V����
	ActionState Update(const float& elapsedTime);
	//��Ԃɓ�������
	void Enter();
	//��Ԃ𔲂�����
	void Exit();
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//���L��
	CharacterEntity* m_bossEnemy;
	//�r�[��
	Beam* m_beam;
	//�r�[���U��
	BossBeamAttackAction* m_beamAttack;
	//�o�ߎ���
	float m_time;

};
