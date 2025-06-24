#pragma once
#include "GameBase/Model/ModelPartsBase.h"



class BossEnemyParts : public ModelPartsBase
{
public:


	//�I�u�W�F�N�g�^�O�̎擾
	ObjectTag GetObjectTag() { return ObjectTag::BOSS_ENEMY_PARTS; }

public:
	//�R���X�g���N�^
	BossEnemyParts(Scene* scene, std::string partsName, std::string modelName);
	//�f�X�g���N�^
	~BossEnemyParts() override  ;


};