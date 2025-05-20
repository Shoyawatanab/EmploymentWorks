/*
	@file	BossJumpAttackCharge.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"

// �O���錾
class CommonResources;
class BossEnemy;
class Beam;
class Player;
class BossJumpAttackAction;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossJumpAttackCharge : public IAction
{

public:

	//�G�t�F�N�g�̑傫��
	static constexpr DirectX::SimpleMath::Vector3 EFFECTE_SCALE{ 5.0f,5.0f,5.0f };
	//�`���[�W����
	static constexpr float CHARGE_TIME = 1.5f;

public:
	//�R���X�g���N�^
	BossJumpAttackCharge(CommonResources* resources,
		BossJumpAttackAction* parent
		,BossEnemy* bossEnemy
		, Player* player);
	//�f�X�g���N�^
	~BossJumpAttackCharge() override ;
	//������
	void Initialize() override;
	//�X�V����
	ActionState Update(const float& elapsedTime)  override ;
	//��Ԃɓ�������
	void Enter() override ;
	//��Ԃ𔲂�����
	void Exit() override;



private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//���L��
	BossEnemy* m_bossEnemy;
	//�v���C��
	Player* m_player;
	//����
	float m_time;
	//�R���g���[���[
	BossJumpAttackAction* m_parent;


};
