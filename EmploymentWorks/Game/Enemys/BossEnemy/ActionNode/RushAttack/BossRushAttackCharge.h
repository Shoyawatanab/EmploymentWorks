/*
	@file	BossRushAttackCharge.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"

// �O���錾
class CommonResources;
class BossEnemy;
class Beam;
class Player;
class BossRushAttackAction;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossRushAttackCharge : public IAction
{
public:
	//�`���[�W����
	static constexpr float CHARGE_TIME = 1.5f;
	//�G�t�F�N�g�̑傫��
	static constexpr DirectX::SimpleMath::Vector3 EFFECTE_SCALE{ 5.0f, 5.0f, 5.0f };


public:
	//�R���X�g���N�^
	BossRushAttackCharge(CommonResources* resources,
		BossRushAttackAction* parent
		,BossEnemy* bossEnemy
		, Player* player);
	//�f�X�g���N�^
	~BossRushAttackCharge() override ;
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
	BossRushAttackAction* m_parent;


};
