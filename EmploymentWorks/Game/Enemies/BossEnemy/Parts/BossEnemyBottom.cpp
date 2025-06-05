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



	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬

	//Pelvis‚Ì¶¬
	auto pelvis = GetScene()->AddActor<BossEnemyPelvis>(GetScene());
	pelvis->GetTransform()->SetParent(GetTransform());

	////LeftThigh‚Ì¶¬
	auto leftThigh = GetScene()->AddActor<BossEnemyLeftThigh>(GetScene());
	leftThigh->GetTransform()->SetParent(GetTransform());

	////RightThigh‚Ì¶¬
	auto rightThigh = GetScene()->AddActor<BossEnemyRightThigh>(GetScene());
	rightThigh->GetTransform()->SetParent(GetTransform());

		//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_BODY_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_BODY_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_BODY_ROTATION);
}

BossEnemyBottom::~BossEnemyBottom()
{
}
