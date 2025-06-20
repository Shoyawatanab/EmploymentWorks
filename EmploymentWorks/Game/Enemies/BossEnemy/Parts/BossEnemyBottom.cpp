#include "pch.h"
#include "BossEnemyBottom.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyBottom::BossEnemyBottom(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME,"BossEnemyBottom")
{



	//�ȉ��ǉ����ʂ̍쐬

	//Pelvis�̐���
	auto pelvis = GetScene()->AddActor<BossEnemyPelvis>(GetScene());
	pelvis->SetParent(this);

	////LeftThigh�̐���
	auto leftThigh = GetScene()->AddActor<BossEnemyLeftThigh>(GetScene());
	leftThigh->SetParent(this);

	////RightThigh�̐���
	auto rightThigh = GetScene()->AddActor<BossEnemyRightThigh>(GetScene());
	rightThigh->SetParent(this);

		//�ʒu���
	GetTransform()->Translate(Params::BOSSENEMY_BODY_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BOSSENEMY_BODY_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BOSSENEMY_BODY_ROTATION);
}

BossEnemyBottom::~BossEnemyBottom()
{
}
