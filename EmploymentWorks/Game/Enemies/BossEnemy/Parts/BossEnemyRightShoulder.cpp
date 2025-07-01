#include "pch.h"
#include "BossEnemyRightShoulder.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyRightShoulder::BossEnemyRightShoulder(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyShoulder"
		, Params::BOSSENEMY_RIGHTSHOULDER_HP
		, Params::BOSSENEMY_RIGHTSHOULDER_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_RIGHTSHOULDER_SPHERE_COLLIDER_SIZE
		, boss)
{


	//�ȉ��ǉ����ʂ̍쐬
//RightArmJoint�̐���
	auto rightArmJoint = GetScene()->AddActor<BossEnemyRightArmJoint>(GetScene(), boss);
	rightArmJoint->SetParent(this);

	//�ʒu���
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTSHOULDER_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTSHOULDER_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTSHOULDER_ROTATION);



}

BossEnemyRightShoulder::~BossEnemyRightShoulder()
{
}
