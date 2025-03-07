/*
	@file	BossBeamAttackShot.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActionState.h"

// �O���錾
class CommonResources;
class BossEnemy;
class Beam;
class BossBeamAttackAction;
class Player;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossBeamAttackShot : public IActionState
{
public:
	BossBeamAttackShot(CommonResources* resources
		, BossEnemy* bossEnemy
		, Beam* beam
		, BossBeamAttackAction* beamAttack
		, Player* player);

	//�p���֌W
	//�f�X�g���N�^
	~BossBeamAttackShot() override;
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
	Player* m_player;

};
