#pragma once
#include "GameBase/Model/ModelBase.h"

class BossEnemy;

class BossEnemyModel : public ModelBase
{
public:
	//�R���X�g���N�^
	BossEnemyModel(Scene* scene, BossEnemy* boss);
	//�f�X�g���N�^
	~BossEnemyModel() override;
	

};