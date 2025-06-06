#include "pch.h"
#include "BossEnemyLeftThigh.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyLeftThigh::BossEnemyLeftThigh(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyThigh")
{




	//以下追加部位の作成
	//LeftLegの生成
	auto leftLeg = GetScene()->AddActor<BossEnemyLeftLeg>(GetScene());
	leftLeg->GetTransform()->SetParent(GetTransform());

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_LEFTTHIGH_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTTHIGH_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTTHIGH_ROTATION);

}

BossEnemyLeftThigh::~BossEnemyLeftThigh()
{
}
