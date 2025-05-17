/*
	@file	BossBeamAttackAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Entities/ActionStateController.h"
#include "Game/Interface/IObserver.h"


// �O���錾
class CommonResources;
class CharacterEntity;
class Beam;
class BossBeamAttackPreliminaryAction;
class BossBeamAttackCharge;
class BossBeamAttackShot;
class BossBeamAttackEnd;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossBeamAttackAction : public ActionStateController, IObserver<GameMessageType>
{

public:

public:
	BossBeamAttackAction(CommonResources* resources,
		CharacterEntity* bossEnemy
		, Beam* beam
		, CharacterEntity* player);
	//�f�X�g���N�^
	~BossBeamAttackAction() ;

	//IObserver
//�ʒm���ɌĂ΂��֐�
	void Notify(const Telegram<GameMessageType>& telegram)  override;



private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	std::unique_ptr<BossBeamAttackPreliminaryAction> m_preliminaryAction;

	std::unique_ptr<BossBeamAttackCharge> m_charge;

	std::unique_ptr<BossBeamAttackShot> m_shot;

	std::unique_ptr<BossBeamAttackEnd> m_attackEnd;

};
