/*
	@file	BossBeamAttackCharge.h
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


class BossBeamAttackCharge : public IAction
{
public:
	//�R���X�g���N�^
	BossBeamAttackCharge(CommonResources* resources
		, CharacterEntity* bossEnemy
		, Beam* beam
		, BossBeamAttackAction* beamAttack);


	//�f�X�g���N�^
	~BossBeamAttackCharge() override;
	//������
	void Initialize() override;
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
	CharacterEntity* m_bossEnemy;
	//�r�[��
	Beam* m_beam;
	//����
	float m_time;
	//�p�[�e�B�N����������
	float m_particleCreateTime;


};
