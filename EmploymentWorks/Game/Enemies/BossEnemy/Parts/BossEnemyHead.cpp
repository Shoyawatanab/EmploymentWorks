#include "pch.h"
#include "BossEnemyHead.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

BossEnemyHead::BossEnemyHead(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyHead")
{

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_HEAD_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_HEAD_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_HEAD_ROTATION);

	//以下追加部位の作成


}

BossEnemyHead::~BossEnemyHead()
{
}
