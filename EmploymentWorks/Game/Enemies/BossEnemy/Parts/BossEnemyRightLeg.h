#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyRightLeg : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "RightLeg";

public:
	//�R���X�g���N�^
	BossEnemyRightLeg(Scene* scene);
	//�f�X�g���N�^
	~BossEnemyRightLeg() override;

};