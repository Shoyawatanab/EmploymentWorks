#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyRightArm : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "RightArm";

public:
	//�R���X�g���N�^
	BossEnemyRightArm(Scene* scene);
	//�f�X�g���N�^
	~BossEnemyRightArm() override;

};