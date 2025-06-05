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

	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬
//RightLeg‚Ì¶¬
	auto rightLeg = GetScene()->AddActor<BossEnemyRightLeg>(GetScene());
	rightLeg->GetTransform()->SetParent(GetTransform());

	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTTHIGH_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTTHIGH_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTTHIGH_ROTATION);



}

BossEnemyRightThigh::~BossEnemyRightThigh()
{
}
