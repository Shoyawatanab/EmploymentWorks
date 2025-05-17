/*
	@file	BossBeamAttackShot.h
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


class BossBeamAttackShot : public IAction
{
public:
	BossBeamAttackShot(CommonResources* resources
		, CharacterEntity* bossEnemy
		, Beam* beam
		, BossBeamAttackAction* beamAttack
		, CharacterEntity* player);

	//�p���֌W
	//�f�X�g���N�^
	~BossBeamAttackShot() override;
	//������
	void Initialize() override;
	// �X�V����
	ActionState Update(const float& elapsedTime);
	//��Ԃɓ�������
	void Enter();
	//��Ԃ𔲂�����
	void Exit();
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	CharacterEntity* m_bossEnemy;
	Beam* m_beam;
	BossBeamAttackAction* m_beamAttack;
	CharacterEntity* m_player;

};
