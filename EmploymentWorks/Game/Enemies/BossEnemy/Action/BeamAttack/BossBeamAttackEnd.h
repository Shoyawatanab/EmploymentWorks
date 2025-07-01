/*
	@file	BossBeamAttackEnd.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// �O���錾
class CommonResources;
class BossEnemyBeam;
class BossBeamAttackActionController;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossBeamAttackEnd : public IAction
{
public:

	//�I�����̎��ԁ@�@�A�j���[�V�����I�����ƍ��킹��
	static constexpr float END_TIME = { 2.0f };

public:
	//�R���X�g���N�^
	BossBeamAttackEnd(Actor* bossEnemy
		, BossEnemyBeam* beam
		, BossBeamAttackActionController* beamAttack);


	//�f�X�g���N�^
	~BossBeamAttackEnd() override ;
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
	Actor* m_bossEnemy;
	//�r�[��
	BossEnemyBeam* m_beam;
	//�r�[���U��
	BossBeamAttackActionController* m_beamAttack;
	//�o�ߎ���
	float m_time;
	//��Ԃɒ��������̃X�P�[��
	DirectX::SimpleMath::Vector3 m_initalScale;

};
