#pragma once
#include <pch.h>
#include "Game/Interface/IActionState.h"

#include "Game/Entities/CollisionEntity.h"

class CommonResources;
class Boomerang;
class Beam;
class Pillar;
class StageObjectManager;
class RisingPillarvAction;

// RisingPillarRiseクラスを定義する
class RisingPillarRise : public IActionState
{
public:
	// コンストラクタ
	RisingPillarRise(RisingPillarvAction* risingPillarvAction , StageObjectManager* stageObjectManager);
	// デストラクタ
	~RisingPillarRise();
	//初期化
	void Initialize(CommonResources* resources) override;
	// 更新する
	IBehaviorNode::State Update(const float& elapsedTime);
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;


private:

	// 共通リソース
	CommonResources* m_commonResources;
	CollisionEntity* m_pillar;
	StageObjectManager* m_stageObjectManager;
	RisingPillarvAction* m_risingPillarvAction;

};

