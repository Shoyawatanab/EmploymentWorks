#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyRightLeg : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "RightLeg";

public:
	//�R���X�g���N�^
	BossEnemyRightLeg(Scene* scene, BossEnemy* boss);
	//�f�X�g���N�^
	~BossEnemyRightLeg() override;

};