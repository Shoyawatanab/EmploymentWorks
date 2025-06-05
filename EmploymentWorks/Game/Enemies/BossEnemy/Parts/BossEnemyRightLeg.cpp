#include "pch.h"
#include "BossEnemyRightLeg.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

BossEnemyRightLeg::BossEnemyRightLeg(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyLeg")
{

	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTLEG_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTLEG_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTLEG_ROTATION);

	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬


}

BossEnemyRightLeg::~BossEnemyRightLeg()
{
}
