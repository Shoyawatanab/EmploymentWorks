/*
	@file	BossBeamAttackShot.h
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


class BossBeamAttackShot : public IAction
{
public:

	//ターゲットのオフセット
	static constexpr DirectX::SimpleMath::Vector3 TARGET_OFFSET{ 0.0f,1.0f,0.0f };

public:
	//コンストラクタ
	BossBeamAttackShot(CommonResources* resources
		, CharacterEntity* bossEnemy
		, Beam* beam
		, BossBeamAttackAction* beamAttack
		, CharacterEntity* player);

	//デストラクタ
	~BossBeamAttackShot() override;
	//初期化
	void Initialize() override;
	// 更新処理
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
	//プレイヤ
	CharacterEntity* m_player;

};
