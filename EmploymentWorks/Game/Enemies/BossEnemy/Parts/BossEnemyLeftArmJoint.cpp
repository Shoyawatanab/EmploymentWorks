#include "pch.h"
#include "BossEnemyLeftArmJoint.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyLeftArmJoint::BossEnemyLeftArmJoint(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyArmJoint")
{



	//�ȉ��ǉ����ʂ̍쐬

	auto leftArm = GetScene()->AddActor<BossEnemyLeftArm>(GetScene());
	leftArm->GetTransform()->SetParent(GetTransform());


	//�ʒu���
	GetTransform()->Translate(Params::BOSSENEMY_LEFTARMJOINT_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTARMJOINT_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTARMJOINT_ROTATION);
}

BossEnemyLeftArmJoint::~BossEnemyLeftArmJoint()
{
}
