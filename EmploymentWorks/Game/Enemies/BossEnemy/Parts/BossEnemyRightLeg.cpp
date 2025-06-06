#include "pch.h"
#include "BossEnemyRightLeg.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

BossEnemyRightLeg::BossEnemyRightLeg(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyLeg")
{

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTLEG_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTLEG_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTLEG_ROTATION);

	//以下追加部位の作成


}

BossEnemyRightLeg::~BossEnemyRightLeg()
{
}
