/*
	@file	BossBeamAttackActionController.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "GameBase/Action/ActionController.h"
#include "GameBase/Actor.h"
#include "Game/Enemies/BossEnemy/Action/BeamAttack/BossBeamAttackCharge.h"
#include "Game/Enemies/BossEnemy/Action/BeamAttack/BossBeamAttackEnd.h"
#include "Game/Enemies/BossEnemy/Action/BeamAttack/BossBeamAttackPreliminaryAction.h"
#include "Game/Enemies/BossEnemy/Action/BeamAttack/BossBeamAttackShot.h"

#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

// �O���錾
class CommonResources;
class BossEnemyBeam;
class BossEnemy;

class BossBeamAttackActionController : public ActionController , public IObserver<SceneMessageType>
{
public:
	//�R���X�g���N�^
	BossBeamAttackActionController(BossEnemy* bossEnemy
		, BossEnemyBeam* beam
		, Actor* player);
	//�f�X�g���N�^
	~BossBeamAttackActionController() override;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas);


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�\������
	std::unique_ptr<BossBeamAttackPreliminaryAction> m_preliminaryAction;
	//�`���[�W
	std::unique_ptr<BossBeamAttackCharge> m_charge;
	//�V���b�g
	std::unique_ptr<BossBeamAttackShot> m_shot;
	//�U���I��
	std::unique_ptr<BossBeamAttackEnd> m_attackEnd;

};
