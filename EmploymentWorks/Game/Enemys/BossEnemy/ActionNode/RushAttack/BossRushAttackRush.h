/*
	@file	BossRushAttackRush.h
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


class BossRushAttackRush : public IAction
{


public:
	BossRushAttackRush(CommonResources* resources,
		BossRushAttackAction* parent
		,BossEnemy* bossEnemy
		, Player* player);
	//�f�X�g���N�^
	~BossRushAttackRush() override ;

	void Initialize() override;

	IBehaviorNode::State Update(const float& elapsedTime)  override ;
	//��Ԃɓ�������
	void Enter() override ;
	//��Ԃ𔲂�����
	void Exit() override;

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	BossEnemy* m_bossEnemy;
	Player* m_player;
	BossRushAttackAction* m_parent;


	DirectX::SimpleMath::Vector3 m_jumpDirection;


};
