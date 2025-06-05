#include "pch.h"
#include "BossEnemyRightArm.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

BossEnemyRightArm::BossEnemyRightArm(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyArm")
{

	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTARM_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTARM_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTARM_ROTATION);

	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬


}

BossEnemyRightArm::~BossEnemyRightArm()
{
}
