#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyLeftArm : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "LeftArm";

public:
	//�R���X�g���N�^
	BossEnemyLeftArm(Scene* scene);
	//�f�X�g���N�^
	~BossEnemyLeftArm() override;

};