/*
	クラス名     : BossEnemyBeam
	説明         : ボス敵のビームクラス
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"

class BossEnemyBeamEnergyBall;
class BossEnemyBeamRays;

class BossEnemyBeam : public Actor
{
public:
	//弾の取得
	BossEnemyBeamEnergyBall* GetEnergyBall() { return m_energyBall; }
	//光線の取得
	BossEnemyBeamRays* GetRays() { return m_rays; }

	void SetTarget(Actor* target) { m_target = target; }

public:
	//コンストラク
	BossEnemyBeam(Scene* scene);
	//デストラクタ
	~BossEnemyBeam();
	//ターゲットに向けて回転
	void TargetToRotation();

private:
	//光線
	BossEnemyBeamRays* m_rays;
	//弾
	BossEnemyBeamEnergyBall* m_energyBall;
	//ターゲット
	Actor* m_target;

};


