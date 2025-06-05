#include "pch.h"
#include "BossEnemyLeftArmJoint.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyLeftArmJoint::BossEnemyLeftArmJoint(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyArmJoint")
{



	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬

	auto leftArm = GetScene()->AddActor<BossEnemyLeftArm>(GetScene());
	leftArm->GetTransform()->SetParent(GetTransform());


	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_LEFTARMJOINT_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTARMJOINT_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTARMJOINT_ROTATION);
}

BossEnemyLeftArmJoint::~BossEnemyLeftArmJoint()
{
}
