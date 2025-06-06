#include "pch.h"
#include "BossEnemyPelvis.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyPelvis::BossEnemyPelvis(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyPelvis")
{

	//以下追加部位の作成
//Torsoの生成
	auto torso = GetScene()->AddActor<BossEnemyTorso>(GetScene());
	torso->GetTransform()->SetParent(GetTransform());

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_PELVIS_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_PELVIS_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_PELVIS_ROTATION);



}

BossEnemyPelvis::~BossEnemyPelvis()
{
}
