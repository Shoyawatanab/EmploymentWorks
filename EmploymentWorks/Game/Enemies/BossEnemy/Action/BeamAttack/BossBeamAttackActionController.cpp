/*
	@file	BossBeamAttackActionController.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossBeamAttackActionController.h"
#include "GameBase/Common/Commons.h"
#include "Game/Params.h"




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
BossBeamAttackActionController::BossBeamAttackActionController(Actor* bossenemy
	, BossEnemyBeam* beam
	, Actor* player)
	:
	m_commonResources{}
	,m_preliminaryAction{}
	,m_charge{}
	,m_shot{}
	,m_attackEnd{}
{
	//各状態の生成
	m_preliminaryAction = std::make_unique<BossBeamAttackPreliminaryAction>(bossenemy,beam,this);
	m_charge = std::make_unique<BossBeamAttackCharge>( bossenemy, beam,this);
	m_shot = std::make_unique<BossBeamAttackShot>( bossenemy, beam,this,player);
	m_attackEnd = std::make_unique<BossBeamAttackEnd>( bossenemy, beam,this);



	//行動順に追加
	AddAction(
		{
		m_preliminaryAction.get()
		,m_charge.get()
		,m_shot.get()
		,m_attackEnd.get()
		}
	);

}

/// <summary>
/// デストラクタ
/// </summary>
BossBeamAttackActionController::~BossBeamAttackActionController()
{
}





