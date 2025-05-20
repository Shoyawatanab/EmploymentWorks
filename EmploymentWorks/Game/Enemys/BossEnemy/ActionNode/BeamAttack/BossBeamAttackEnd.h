/*
	@file	BossBeamAttackEnd.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"

// 前方宣言
class CommonResources;
class CharacterEntity;
class Beam;
class BossBeamAttackAction;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossBeamAttackEnd : public IAction
{

public:
	//コンストラクタ
	BossBeamAttackEnd(CommonResources* resources
		, CharacterEntity* bossEnemy
		, Beam* beam
		, BossBeamAttackAction* beamAttack);


	//デストラクタ
	~BossBeamAttackEnd() override ;
	//初期化
	void Initialize() override ;
	// 更新する
	ActionState Update(const float& elapsedTime);
	//状態に入った時
	void Enter();
	//状態を抜けた時
	void Exit();
private:
	// 共通リソース
	CommonResources* m_commonResources;
	//所有者
	CharacterEntity* m_bossEnemy;
	//ビーム
	Beam* m_beam;
	//ビーム攻撃
	BossBeamAttackAction* m_beamAttack;
	//経過時間
	float m_time;

};
