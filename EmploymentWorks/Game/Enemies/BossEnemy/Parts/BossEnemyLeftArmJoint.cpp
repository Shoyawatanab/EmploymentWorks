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



	//以下追加部位の作成

	auto leftArm = GetScene()->AddActor<BossEnemyLeftArm>(GetScene());
	leftArm->GetTransform()->SetParent(GetTransform());


	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_LEFTARMJOINT_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTARMJOINT_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTARMJOINT_ROTATION);
}

BossEnemyLeftArmJoint::~BossEnemyLeftArmJoint()
{
}
