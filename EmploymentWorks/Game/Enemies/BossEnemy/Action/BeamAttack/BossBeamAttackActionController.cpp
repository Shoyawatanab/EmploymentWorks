/*
	�N���X��     : BossBeamAttackActionController
	����         : �{�X�G�̃r�[���U���̃R���g���[���[
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "BossBeamAttackActionController.h"
#include "GameBase/Common/Commons.h"
#include "Game/Params.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Component/Components.h"
#include "Game/Enemies/BossEnemy/Beam/BossEnemyBeam.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
BossBeamAttackActionController::BossBeamAttackActionController(BossEnemy* bossenemy
	, BossEnemyBeam* beam
	, Actor* player)
	:
	m_commonResources{}
	,m_preliminaryAction{}
	,m_charge{}
	,m_shot{}
	,m_attackEnd{}
	,m_beam{beam}
{
	//�e��Ԃ̐���
	m_preliminaryAction = std::make_unique<BossBeamAttackPreliminaryAction>(bossenemy,beam,this);
	m_charge = std::make_unique<BossBeamAttackCharge>( bossenemy, beam,this);
	m_shot = std::make_unique<BossBeamAttackShot>( bossenemy, beam,this,player);
	m_attackEnd = std::make_unique<BossBeamAttackEnd>( bossenemy, beam,this);



	//�s�����ɒǉ�
	AddAction(
		{
		m_preliminaryAction.get()
		,m_charge.get()
		,m_shot.get()
		,m_attackEnd.get()
		}
	);


	//�ʒm���󂯎��R���|�[�l���g�̒ǉ�
	auto ob = bossenemy->AddComponent<ObserverComponent<SceneMessageType>>(bossenemy);
	//�ǂ̒ʒm���̓o�^�ƌĂяo���֐��̓o�^
	ob->Rigister(
		{
			SceneMessageType::BOSS_BEAM_IMPACT
		}
		, std::bind(&BossBeamAttackActionController::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossBeamAttackActionController::~BossBeamAttackActionController()
{
}

/// <summary>
/// �ʒm���ɌĂяo���֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void BossBeamAttackActionController::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);
	switch (type)
	{
		case SceneMessageType::BOSS_BEAM_IMPACT:
			//�X�e�[�g��Shot����End�ɕύX
			ChangeState();
			break;
		default:
			break;
	}

}

/// <summary>
/// �s���̒��~
/// </summary>
void BossBeamAttackActionController::ActionCancel()
{

	m_beam->SetActive(false);
}





