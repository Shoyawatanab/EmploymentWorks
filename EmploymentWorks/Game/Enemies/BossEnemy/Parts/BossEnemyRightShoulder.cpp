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

	//以下追加部位の作成
//RightArmJointの生成
	auto rightArmJoint = GetScene()->AddActor<BossEnemyRightArmJoint>(GetScene());
	rightArmJoint->GetTransform()->SetParent(GetTransform());

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTSHOULDER_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTSHOULDER_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTSHOULDER_ROTATION);



}

BossEnemyRightShoulder::~BossEnemyRightShoulder()
{
}
