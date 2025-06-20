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
	pelvis->SetParent(this);

	////LeftThigh‚Ì¶¬
	auto leftThigh = GetScene()->AddActor<BossEnemyLeftThigh>(GetScene());
	leftThigh->SetParent(this);

	////RightThigh‚Ì¶¬
	auto rightThigh = GetScene()->AddActor<BossEnemyRightThigh>(GetScene());
	rightThigh->SetParent(this);

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
