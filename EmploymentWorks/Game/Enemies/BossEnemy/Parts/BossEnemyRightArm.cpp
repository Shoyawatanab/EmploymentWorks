#include "pch.h"
#include "BossEnemyRightArm.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

BossEnemyRightArm::BossEnemyRightArm(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyArm")
{

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTARM_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTARM_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTARM_ROTATION);

	//以下追加部位の作成


}

BossEnemyRightArm::~BossEnemyRightArm()
{
}
