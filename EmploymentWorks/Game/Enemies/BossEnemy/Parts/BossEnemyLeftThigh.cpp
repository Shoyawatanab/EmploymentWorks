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




	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬
	//LeftLeg‚Ì¶¬
	auto leftLeg = GetScene()->AddActor<BossEnemyLeftLeg>(GetScene());
	leftLeg->SetParent(this);

	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_LEFTTHIGH_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTTHIGH_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTTHIGH_ROTATION);

}

BossEnemyLeftThigh::~BossEnemyLeftThigh()
{
}
