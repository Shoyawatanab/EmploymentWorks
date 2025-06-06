#include "pch.h"
#include "BossEnemyLeftArm.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

BossEnemyLeftArm::BossEnemyLeftArm(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyArm")
{

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_LEFTARM_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTARM_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTARM_ROTATION);

	//以下追加部位の作成


}

BossEnemyLeftArm::~BossEnemyLeftArm()
{
}
