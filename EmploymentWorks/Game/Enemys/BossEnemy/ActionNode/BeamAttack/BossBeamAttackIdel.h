/*
	@file	BossBeamAttackIdel.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActionState.h"

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


class BossBeamAttackIdel : public IActionState
{

public:
	BossBeamAttackIdel(CommonResources* resources
		, BossEnemy* bossEnemy
		, Beam* beam
	,BossBeamAttackAction* beamAttack);

//�p���֌W
	//�f�X�g���N�^
	~BossBeamAttackIdel() override ;
	//������
	void Initialize(CommonResources* resources);
	// �X�V����
	IBehaviorNode::State Update(const float& elapsedTime);
	//��Ԃɓ�������
	void Enter();
	//��Ԃ𔲂�����
	void Exit();
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	BossEnemy* m_bossEnemy;
	Beam* m_beam;
	BossBeamAttackAction* m_beamAttack;

};
