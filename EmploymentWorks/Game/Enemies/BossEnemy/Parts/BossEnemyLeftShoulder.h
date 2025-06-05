#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyLeftShoulder : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "LeftShoulder";

public:
	//�R���X�g���N�^
	BossEnemyLeftShoulder(Scene* scene);
	//�f�X�g���N�^
	~BossEnemyLeftShoulder() override;

};