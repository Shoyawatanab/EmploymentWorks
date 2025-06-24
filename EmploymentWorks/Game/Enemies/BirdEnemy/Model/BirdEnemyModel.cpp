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

	//�q�����f�����擾
	auto parts = body->GetAllDescendants();
	//�q�����f�����p�[�c�ɓo�^
	AddParts(parts);
	


}

BirdEnemyModel::~BirdEnemyModel()
{
}
