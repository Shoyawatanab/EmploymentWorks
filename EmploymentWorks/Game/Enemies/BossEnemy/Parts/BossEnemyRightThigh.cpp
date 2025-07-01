#include "pch.h"
#include "BossEnemyRightThigh.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyRightThigh::BossEnemyRightThigh(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyThigh"
		, Params::BOSSENEMY_RIGHTTHIGH_HP
		, Params::BOSSENEMY_RIGHTTHIGH_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_RIGHTTHIGH_SPHERE_COLLIDER_SIZE
		, boss)
{


	//�ȉ��ǉ����ʂ̍쐬
//RightLeg�̐���
	auto rightLeg = GetScene()->AddActor<BossEnemyRightLeg>(GetScene(), boss);
	rightLeg->SetParent(this);

	//�ʒu���
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTTHIGH_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTTHIGH_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTTHIGH_ROTATION);



}

BossEnemyRightThigh::~BossEnemyRightThigh()
{
}
