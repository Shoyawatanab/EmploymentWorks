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



	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬
	//Head1‚Ì¶¬
	auto head = GetScene()->AddActor<BossEnemyHead>(GetScene());
	head->SetParent(this);

	//LeftShouder‚Ì¶¬
	auto leftShouder = GetScene()->AddActor<BossEnemyLeftShoulder>(GetScene());
	leftShouder->SetParent(this);

	//RightShouder‚Ì¶¬
	auto rightShouder = GetScene()->AddActor<BossEnemyRightShoulder>(GetScene());
	rightShouder->SetParent(this);

	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_TORSO_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_TORSO_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_TORSO_ROTATION);

}

BossEnemyTorso::~BossEnemyTorso()
{
}
