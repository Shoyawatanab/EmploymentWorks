#include "pch.h"
#include "BossEnemyHead.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

BossEnemyHead::BossEnemyHead(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyHead"
		, Params::BOSSENEMY_HEAD_HP
		, Params::BOSSENEMY_HEAD_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_HEAD_SPHERE_COLLIDER_SIZE
		,boss)
{
	
	//�ʒu���
	GetTransform()->Translate(Params::BOSSENEMY_HEAD_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BOSSENEMY_HEAD_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BOSSENEMY_HEAD_ROTATION);

	//�ȉ��ǉ����ʂ̍쐬


}

BossEnemyHead::~BossEnemyHead()
{
}
