#include "pch.h"
#include "BossEnemyHead.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

BossEnemyHead::BossEnemyHead(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyHead")
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
