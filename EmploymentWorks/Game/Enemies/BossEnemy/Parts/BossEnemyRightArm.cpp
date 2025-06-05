#include "pch.h"
#include "BossEnemyRightArm.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

BossEnemyRightArm::BossEnemyRightArm(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyArm")
{

	//�ʒu���
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTARM_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTARM_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTARM_ROTATION);

	//�ȉ��ǉ����ʂ̍쐬


}

BossEnemyRightArm::~BossEnemyRightArm()
{
}
