#pragma once
#include "Game/Enemies/BirdEnemy/BirdEnemyParts.h"

class BirdEnemyLeftFeather : public BirdEnemyPars
{

public:

	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "LeftFeaather";

public:
	//�R���X�g���N
	BirdEnemyLeftFeather(Scene* scene);
	//�f�X�g���N�^
	~BirdEnemyLeftFeather() override;


};



