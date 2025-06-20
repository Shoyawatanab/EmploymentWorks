/*
	@file	BossBeamAttackShot.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// �O���錾
class CommonResources;
class Beam;
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

public:
	//�R���X�g���N�^
	BossBeamAttackShot(Actor* bossEnemy
		, Beam* beam
		, BossBeamAttackActionController* beamAttack
		, Actor* player);

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
	//���L��
	Actor* m_bossEnemy;
	//�r�[��
	Beam* m_beam;
	//�r�[���U��
	BossBeamAttackActionController* m_beamAttack;
	//�v���C��
	Actor* m_player;

};
