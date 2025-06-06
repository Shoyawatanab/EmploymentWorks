#include "pch.h"
#include "BossEnemyRightThigh.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyRightThigh::BossEnemyRightThigh(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyThigh")
{

	//以下追加部位の作成
//RightLegの生成
	auto rightLeg = GetScene()->AddActor<BossEnemyRightLeg>(GetScene());
	rightLeg->GetTransform()->SetParent(GetTransform());

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTTHIGH_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTTHIGH_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTTHIGH_ROTATION);



}

BossEnemyRightThigh::~BossEnemyRightThigh()
{
}
