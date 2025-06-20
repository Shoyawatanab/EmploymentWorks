#include "pch.h"
#include "BossEnemyTorso.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyTorso::BossEnemyTorso(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyTorso")
{



	//�ȉ��ǉ����ʂ̍쐬
	//Head1�̐���
	auto head = GetScene()->AddActor<BossEnemyHead>(GetScene());
	head->SetParent(this);

	//LeftShouder�̐���
	auto leftShouder = GetScene()->AddActor<BossEnemyLeftShoulder>(GetScene());
	leftShouder->SetParent(this);

	//RightShouder�̐���
	auto rightShouder = GetScene()->AddActor<BossEnemyRightShoulder>(GetScene());
	rightShouder->SetParent(this);

	//�ʒu���
	GetTransform()->Translate(Params::BOSSENEMY_TORSO_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BOSSENEMY_TORSO_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BOSSENEMY_TORSO_ROTATION);

}

BossEnemyTorso::~BossEnemyTorso()
{
}
