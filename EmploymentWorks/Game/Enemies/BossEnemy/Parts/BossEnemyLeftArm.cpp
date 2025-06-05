#include "pch.h"
#include "BossEnemyLeftArm.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

BossEnemyLeftArm::BossEnemyLeftArm(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyArm")
{

	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_LEFTARM_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTARM_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTARM_ROTATION);

	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬


}

BossEnemyLeftArm::~BossEnemyLeftArm()
{
}
