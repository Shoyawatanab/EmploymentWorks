#pragma once
#include "GameBase/Model/ModelPartsBase.h"


class BirdEnemyPars : public  ModelPartsBase
{
public:

	//�I�u�W�F�N�g�^�O�̎擾
	ObjectTag GetObjectTag() override { return ObjectTag::BOSS_ENEMY_PARTS; }

public:
	//�R���X�g���N
	BirdEnemyPars(Scene* scene,const  std::string& partsName, const std::string& modelName);
	//�f�X�g���N�^
	~BirdEnemyPars() override;

};


