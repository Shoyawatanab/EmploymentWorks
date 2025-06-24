#include "pch.h"
#include "BirdEnemyBody.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Enemies/BirdEnemy/BirdEnemyPartss.h"


BirdEnemyBody::BirdEnemyBody(Scene* scene)
	:
	BirdEnemyPars(scene,PARTS_NAME,"BirdEnemyBody")
{

	auto leftFeather = GetScene()->AddActor<BirdEnemyLeftFeather>(GetScene());
	leftFeather->SetParent(this);

	auto rightFeather = GetScene()->AddActor<BirdEnemyRightFeather>(GetScene());
	rightFeather->SetParent(this);

	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BIRDENEMY_BODY_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BIRDENEMY_BODY_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BIRDENEMY_BODY_ROTATION);

}

BirdEnemyBody::~BirdEnemyBody()
{
}
