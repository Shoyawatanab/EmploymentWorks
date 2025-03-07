/*
	@file	BarrierPreliminaryAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActionState.h"

// �O���錾
class CommonResources;
class BossEnemy;
class BarrierDefenseAction;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}



class BarrierPreliminaryAction : public IActionState
{
public:
	BarrierPreliminaryAction(
		BarrierDefenseAction* barrierDefenseAction,
		BossEnemy* bossEnemy
		);


	//�f�X�g���N�^
	~BarrierPreliminaryAction() override;
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

	//�o�ߎ���
	float m_time;

	BossEnemy* m_bossEnemy;
	BarrierDefenseAction* m_barrierDefenseAction;


};
