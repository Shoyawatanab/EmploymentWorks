#include "pch.h"
#include "BossEnemyRightShoulder.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyRightShoulder::BossEnemyRightShoulder(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyShoulder")
{

	//�ȉ��ǉ����ʂ̍쐬
//RightArmJoint�̐���
	auto rightArmJoint = GetScene()->AddActor<BossEnemyRightArmJoint>(GetScene());
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
