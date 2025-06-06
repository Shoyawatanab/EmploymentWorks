#include "pch.h"
#include "BossEnemyLeftLeg.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

BossEnemyLeftLeg::BossEnemyLeftLeg(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyLeg")
{

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_LEFTLEG_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTLEG_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTLEG_ROTATION);

	//以下追加部位の作成


}

BossEnemyLeftLeg::~BossEnemyLeftLeg()
{
}
