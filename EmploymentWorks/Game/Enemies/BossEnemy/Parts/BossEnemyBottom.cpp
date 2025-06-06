#include "pch.h"
#include "BossEnemyBottom.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyBottom::BossEnemyBottom(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME,"BossEnemyBottom")
{



	//以下追加部位の作成

	//Pelvisの生成
	auto pelvis = GetScene()->AddActor<BossEnemyPelvis>(GetScene());
	pelvis->GetTransform()->SetParent(GetTransform());

	////LeftThighの生成
	auto leftThigh = GetScene()->AddActor<BossEnemyLeftThigh>(GetScene());
	leftThigh->GetTransform()->SetParent(GetTransform());

	////RightThighの生成
	auto rightThigh = GetScene()->AddActor<BossEnemyRightThigh>(GetScene());
	rightThigh->GetTransform()->SetParent(GetTransform());

		//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_BODY_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_BODY_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_BODY_ROTATION);
}

BossEnemyBottom::~BossEnemyBottom()
{
}
