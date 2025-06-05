#include "pch.h"
#include "BossEnemyRightArmJoint.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyRightArmJoint::BossEnemyRightArmJoint(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyArmJoint")
{
	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬
//RightArm‚Ì¶¬
	auto rightArm = GetScene()->AddActor<BossEnemyRightArm>(GetScene());
	rightArm->GetTransform()->SetParent(GetTransform());

	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTARMJOINT_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTARMJOINT_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTARMJOINT_ROTATION);



}

BossEnemyRightArmJoint::~BossEnemyRightArmJoint()
{
}
