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
	//以下追加部位の作成
//RightArmの生成
	auto rightArm = GetScene()->AddActor<BossEnemyRightArm>(GetScene());
	rightArm->GetTransform()->SetParent(GetTransform());

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTARMJOINT_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTARMJOINT_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTARMJOINT_ROTATION);



}

BossEnemyRightArmJoint::~BossEnemyRightArmJoint()
{
}
