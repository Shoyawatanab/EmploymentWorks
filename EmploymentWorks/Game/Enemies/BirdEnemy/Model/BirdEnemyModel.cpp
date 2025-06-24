#include "pch.h"
#include "BirdEnemyModel.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Enemies/BirdEnemy/BirdEnemyPartss.h"
#include "GameBase/Component/Components.h"

BirdEnemyModel::BirdEnemyModel(Scene* scene)
	:
	ModelBase(scene)
{

	auto body = GetScene()->AddActor<BirdEnemyBody>(GetScene());
	body->GetTransform()->SetParent(GetTransform());

	//子孫モデルを取得
	auto parts = body->GetAllDescendants();
	//子孫モデルをパーツに登録
	AddParts(parts);
	


}

BirdEnemyModel::~BirdEnemyModel()
{
}
