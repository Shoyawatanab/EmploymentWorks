/*
	@file	RisingPillarPreliminaryAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActionState.h"

// �O���錾
class CommonResources;
class BossEnemy;
class RisingPillarvAction;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}



class RisingPillarPreliminaryAction : public IActionState
{
public:
	RisingPillarPreliminaryAction(
		RisingPillarvAction* risingPillarvAction,
		BossEnemy* bossEnemy
		);
	//�f�X�g���N�^
	~RisingPillarPreliminaryAction() override;
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
	RisingPillarvAction* m_risingPillarvAction;


};
