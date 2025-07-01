#include "pch.h"
#include "BossEnemyLeftShoulder.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyLeftShoulder::BossEnemyLeftShoulder(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene, PARTS_NAME
		, "BossEnemyShoulder"
		, Params::BOSSENEMY_LEFTSHOULDER_HP
		, Params::BOSSENEMY_LEFTSHOULDER_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_LEFTSHOULDER_SPHERE_COLLIDER_SIZE
		, boss)
{



	//�ȉ��ǉ����ʂ̍쐬
//�uLeftArmJoint�v�𐶐�����
	auto leftArmJoint = GetScene()->AddActor<BossEnemyLeftArmJoint>(GetScene(), boss);
	leftArmJoint->SetParent(this);


	//�ʒu���
	GetTransform()->Translate(Params::BOSSENEMY_LEFTSHOULDER_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTSHOULDER_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTSHOULDER_ROTATION);


}

BossEnemyLeftShoulder::~BossEnemyLeftShoulder()
{
}
