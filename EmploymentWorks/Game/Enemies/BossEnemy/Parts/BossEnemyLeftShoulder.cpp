#include "pch.h"
#include "BossEnemyLeftShoulder.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyLeftShoulder::BossEnemyLeftShoulder(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyShoulder")
{
	//�ȉ��ǉ����ʂ̍쐬
//�uLeftArmJoint�v�𐶐�����
	auto leftArmJoint = GetScene()->AddActor<BossEnemyLeftArmJoint>(GetScene());
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
