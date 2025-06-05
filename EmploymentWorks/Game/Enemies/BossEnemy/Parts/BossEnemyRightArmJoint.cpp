#include "pch.h"
#include "BossEnemyRightArmJoint.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyRightArmJoint::BossEnemyRightArmJoint(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyArmJoint")
{
	//�ȉ��ǉ����ʂ̍쐬
//RightArm�̐���
	auto rightArm = GetScene()->AddActor<BossEnemyRightArm>(GetScene());
	rightArm->GetTransform()->SetParent(GetTransform());

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
