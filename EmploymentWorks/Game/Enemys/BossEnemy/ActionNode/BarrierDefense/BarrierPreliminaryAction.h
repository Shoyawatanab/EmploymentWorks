/*
	@file	BarrierPreliminaryAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"

// �O���錾
class CommonResources;
class BossEnemy;
class BarrierDefenseAction;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}



class BarrierPreliminaryAction : public IAction
{
public:
	BarrierPreliminaryAction(CommonResources* resources,
		BarrierDefenseAction* barrierDefenseAction,
		BossEnemy* bossEnemy
		);


	//�f�X�g���N�^
	~BarrierPreliminaryAction() override;
	//������
	void Initialize() override;
	// �X�V����
	ActionState Update(const float& elapsedTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	//�o�ߎ���
	float m_time;

	BossEnemy* m_bossEnemy;
	BarrierDefenseAction* m_barrierDefenseAction;


};
