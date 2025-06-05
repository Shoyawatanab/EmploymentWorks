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

	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬
//Torso‚Ì¶¬
	auto torso = GetScene()->AddActor<BossEnemyTorso>(GetScene());
	torso->GetTransform()->SetParent(GetTransform());

	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_PELVIS_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_PELVIS_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_PELVIS_ROTATION);



}

BossEnemyPelvis::~BossEnemyPelvis()
{
}
