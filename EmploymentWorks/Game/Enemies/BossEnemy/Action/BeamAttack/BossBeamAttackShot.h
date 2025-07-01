/*
	@file	BossBeamAttackShot.h
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


class BossBeamAttackShot : public IAction
{
public:

	//�^�[�Q�b�g�̃I�t�Z�b�g
	static constexpr DirectX::SimpleMath::Vector3 TARGET_OFFSET{ 0.0f,1.0f,0.0f };

	//
	static constexpr float SHOT_SPEED = 20.0f;

public:
	//�R���X�g���N�^
	BossBeamAttackShot(Actor* bossEnemy
		, BossEnemyBeam* beam
		, BossBeamAttackActionController* beamAttack
		, Actor* player);

	//�f�X�g���N�^
	~BossBeamAttackShot() override;
	// �X�V����
	ActionState Update(const float& deltaTime);
	//��Ԃɓ�������
	void Enter();
	//��Ԃ𔲂�����
	void Exit();
private:
	//���L��
	Actor* m_bossEnemy;
	//�r�[��
	BossEnemyBeam* m_beam;
	//�r�[���U��
	BossBeamAttackActionController* m_beamAttack;
	//�v���C��
	Actor* m_player;
	//�ړ�����
	DirectX::SimpleMath::Vector3 m_moveDirection;

};
