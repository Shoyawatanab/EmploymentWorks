#include "pch.h"
#include "BossEnemyLeftArm.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

BossEnemyLeftArm::BossEnemyLeftArm(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyArm")
{

	//�ʒu���
	GetTransform()->Translate(Params::BOSSENEMY_LEFTARM_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTARM_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTARM_ROTATION);

	//�ȉ��ǉ����ʂ̍쐬


}

BossEnemyLeftArm::~BossEnemyLeftArm()
{
}
