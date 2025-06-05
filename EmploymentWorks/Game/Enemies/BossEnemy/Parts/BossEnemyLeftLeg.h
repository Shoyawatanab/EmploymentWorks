#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyLeftLeg : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "LeftLeg";

public:
	//�R���X�g���N�^
	BossEnemyLeftLeg(Scene* scene);
	//�f�X�g���N�^
	~BossEnemyLeftLeg() override;

};