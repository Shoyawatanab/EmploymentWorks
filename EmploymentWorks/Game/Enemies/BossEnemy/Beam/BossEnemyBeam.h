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
public:
	//コンストラク
	BossEnemyBeam(Scene* scene);
	//デストラクタ
	~BossEnemyBeam();

private:
	//光線
	BossEnemyBeamRays* m_rays;
	//弾
	BossEnemyBeamEnergyBall* m_energyBall;
	//ターゲット
	Actor* m_target;

};


