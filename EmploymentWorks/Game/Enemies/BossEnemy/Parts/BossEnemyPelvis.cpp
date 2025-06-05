#include "pch.h"
#include "BossEnemyPelvis.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyPelvis::BossEnemyPelvis(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyPelvis")
{

	//�ȉ��ǉ����ʂ̍쐬
//Torso�̐���
	auto torso = GetScene()->AddActor<BossEnemyTorso>(GetScene());
	torso->GetTransform()->SetParent(GetTransform());

	//�ʒu���
	GetTransform()->Translate(Params::BOSSENEMY_PELVIS_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BOSSENEMY_PELVIS_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BOSSENEMY_PELVIS_ROTATION);



}

BossEnemyPelvis::~BossEnemyPelvis()
{
}
