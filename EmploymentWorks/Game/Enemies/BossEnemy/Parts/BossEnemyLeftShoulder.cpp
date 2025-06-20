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
	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬
//uLeftArmJointv‚ð¶¬‚·‚é
	auto leftArmJoint = GetScene()->AddActor<BossEnemyLeftArmJoint>(GetScene());
	leftArmJoint->SetParent(this);


	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_LEFTSHOULDER_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTSHOULDER_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTSHOULDER_ROTATION);


}

BossEnemyLeftShoulder::~BossEnemyLeftShoulder()
{
}
