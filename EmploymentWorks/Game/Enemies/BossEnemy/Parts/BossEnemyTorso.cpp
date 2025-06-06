#include "pch.h"
#include "BossEnemyTorso.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyTorso::BossEnemyTorso(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyTorso")
{



	//以下追加部位の作成
	//Head1の生成
	auto head = GetScene()->AddActor<BossEnemyHead>(GetScene());
	head->GetTransform()->SetParent(GetTransform());

	//LeftShouderの生成
	auto leftShouder = GetScene()->AddActor<BossEnemyLeftShoulder>(GetScene());
	leftShouder->GetTransform()->SetParent(GetTransform());

	//RightShouderの生成
	auto rightShouder = GetScene()->AddActor<BossEnemyRightShoulder>(GetScene());
	rightShouder->GetTransform()->SetParent(GetTransform());

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_TORSO_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_TORSO_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_TORSO_ROTATION);

}

BossEnemyTorso::~BossEnemyTorso()
{
}
