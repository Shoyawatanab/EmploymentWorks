#pragma once
#include "Game/Enemies/BirdEnemy/BirdEnemyParts.h"

class BirdEnemyRightFeather : public BirdEnemyPars
{

public:

	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "RightFeaather";

public:
	//�R���X�g���N
	BirdEnemyRightFeather(Scene* scene);
	//�f�X�g���N�^
	~BirdEnemyRightFeather() override;


};