#include "pch.h"
#include "BossEnemyLeftLeg.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

BossEnemyLeftLeg::BossEnemyLeftLeg(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyLeg"
		, Params::BOSSENEMY_LEFTLEG_HP
		, Params::BOSSENEMY_LEFTLEG_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_LEFTLEG_SPHERE_COLLIDER_SIZE
		, boss)
{

	//�ʒu���
	GetTransform()->Translate(Params::BOSSENEMY_LEFTLEG_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTLEG_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTLEG_ROTATION);

	//�ȉ��ǉ����ʂ̍쐬


}

BossEnemyLeftLeg::~BossEnemyLeftLeg()
{
}
