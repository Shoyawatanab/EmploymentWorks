#include "pch.h"
#include "BossEnemyHead.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

BossEnemyHead::BossEnemyHead(Scene* scene)
	:
	BossEnemyParts(scene, PARTS_NAME, "BossEnemyHead")
{

	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_HEAD_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_HEAD_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_HEAD_ROTATION);

	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬


}

BossEnemyHead::~BossEnemyHead()
{
}
