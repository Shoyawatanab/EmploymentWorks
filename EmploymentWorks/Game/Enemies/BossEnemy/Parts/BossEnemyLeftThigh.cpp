#include "pch.h"
#include "BossEnemyLeftThigh.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyLeftThigh::BossEnemyLeftThigh(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyThigh"
		, Params::BOSSENEMY_LEFTTHIGH_HP
		, Params::BOSSENEMY_LEFTTHIGH_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_LEFTTHIGH_SPHERE_COLLIDER_SIZE
		, boss)
{



	//�ȉ��ǉ����ʂ̍쐬
	//LeftLeg�̐���
	auto leftLeg = GetScene()->AddActor<BossEnemyLeftLeg>(GetScene(), boss);
	leftLeg->SetParent(this);

	//�ʒu���
	GetTransform()->Translate(Params::BOSSENEMY_LEFTTHIGH_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTTHIGH_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTTHIGH_ROTATION);

}

BossEnemyLeftThigh::~BossEnemyLeftThigh()
{
}
