/*
	@file	RisingPillarvAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"
#include"Game/Interface/IActionState.h"

#include "Game/Enemys/BossEnemy/ActionNode/RisingPillar/RisingPillarIdel.h"
#include "Game/Enemys/BossEnemy/ActionNode/RisingPillar/RisingPillarRise.h"
#include "Game/Enemys/BossEnemy/ActionNode/RisingPillar/RisingPillarPreliminaryAction.h"


// �O���錾
class CommonResources;
class BossEnemy;
class Player;
class Pillar;
class StageObjectManager;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class RisingPillarvAction : public IAction
{

public:


	IActionState* GetCurrentState() { return m_currentState; }

	//��Ԃ̕ύX
	void ChangeState(IActionState* nextState);

	RisingPillarIdel* GetPillarIdel() { return m_idle.get(); }

	RisingPillarRise* GetPillarRise() { return m_rise.get(); }

	RisingPillarPreliminaryAction* GetPillarpreliminaryAction() { return m_preliminaryAction.get(); }

public:
	RisingPillarvAction(CommonResources* resources,
		BossEnemy* bossEnemy
		, Player* player
		, StageObjectManager* stageObjectManger);

	//�f�X�g���N�^
	~RisingPillarvAction() override ;

	void Initialize() override;

	IBehaviorNode::State Update(float elapsdTime)  override ;




private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	IActionState* m_currentState;


	//�ʏ���
	std::unique_ptr<RisingPillarIdel> m_idle;
	//�㏸
	std::unique_ptr<RisingPillarRise> m_rise;
	//�\������
	std::unique_ptr<RisingPillarPreliminaryAction> m_preliminaryAction;

	std::vector<Pillar*> m_pillars;

};
