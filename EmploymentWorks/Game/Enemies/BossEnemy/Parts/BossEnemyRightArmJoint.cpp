#include "pch.h"
#include "BossEnemyRightArmJoint.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyRightArmJoint::BossEnemyRightArmJoint(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyArmJoint"
		, Params::BOSSENEMY_RIGHTARMJOINT_HP
		, Params::BOSSENEMY_RIGHTARMJOINT_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_RIGHTARMJOINT_SPHERE_COLLIDER_SIZE
		, boss)
{
	


	//�ȉ��ǉ����ʂ̍쐬
//RightArm�̐���
	auto rightArm = GetScene()->AddActor<BossEnemyRightArm>(GetScene(), boss);
	rightArm->SetParent(this);

	//�ʒu���
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTARMJOINT_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTARMJOINT_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTARMJOINT_ROTATION);



}

BossEnemyRightArmJoint::~BossEnemyRightArmJoint()
{
}
