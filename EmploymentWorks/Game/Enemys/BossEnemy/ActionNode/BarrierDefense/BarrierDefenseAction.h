/*
	@file	BarrierDefenseAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Entities/ActionStateController.h"
#include "Game/Interface/IObserver.h"

#include "Game/Enemys/BossEnemy/ActionNode/BarrierDefense/BarrierPreliminaryAction.h"
#include "Game/Enemys/BossEnemy/ActionNode/BarrierDefense/BarrierDeployment.h"
#include "Game/Enemys/BossEnemy/ActionNode/BarrierDefense/BarrierClose.h"



// �O���錾
class CommonResources;
class CharacterEntity;
class Barrier;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}



class BarrierDefenseAction : public ActionStateController , IObserver<GameMessageType>
{
public:
	//�R���X�g���N�^
	BarrierDefenseAction(CommonResources* resources,
		CharacterEntity* owner
		,Barrier* barrier
	);

	//�f�X�g���N�^
	~BarrierDefenseAction() ;





	//�ʒm���ɌĂ΂��֐�
	void Notify(const Telegram<GameMessageType>& telegram)  override;



private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�\������
	std::unique_ptr<BarrierPreliminaryAction> m_preliminaryAction;
	//�o���A�W�J
	std::unique_ptr<BarrierDeployment> m_deployment;
	//�o���͂����܂�
	std::unique_ptr<BarrierClose> m_close;
	//�o���A
	Barrier* m_barrier;

};
