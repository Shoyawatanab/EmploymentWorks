/*
	@file	SwingDownAttackAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Entities/ActionStateController.h"
#include "Game/Interface/IObserver.h"
#include "Game/Enemys/BossEnemy/ActionNode/SwingDownAttack/SwingDownAttackRaisePhase.h"
#include "Game/Enemys/BossEnemy/ActionNode/SwingDownAttack/SwingDownAttackSwingPhase.h"


// �O���錾
class CommonResources;
class CharacterEntity;
class Beam;
class Player;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class SwingDownAttackAction : public ActionStateController , IObserver<GameMessageType>
{

public:

	static  constexpr float JUMPPOWER = 0.3f;

	static  constexpr float MOVESPEED = 9.0f;

public:




public:
	SwingDownAttackAction(CommonResources* resources,
		CharacterEntity* owner
		);

	//�f�X�g���N�^
	~SwingDownAttackAction();


	//IObserver
//�ʒm���ɌĂ΂��֐�
	void Notify(const Telegram<GameMessageType>& telegram)  override;


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	//�U��グ
	std::unique_ptr<SwingDownAttackRaisePhase> m_raisePhase;
	//�U�艺�낵
	std::unique_ptr<SwingDownAttackSwingPhase> m_swingPhase;

};
