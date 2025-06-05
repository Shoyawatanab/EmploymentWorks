#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyRightShoulder : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "RightShoulder";

public:
	//�R���X�g���N�^
	BossEnemyRightShoulder(Scene* scene);
	//�f�X�g���N�^
	~BossEnemyRightShoulder() override;

};