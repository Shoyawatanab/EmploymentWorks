#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyLeftShoulder : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "LeftShoulder";

public:
	//�R���X�g���N�^
	BossEnemyLeftShoulder(Scene* scene, BossEnemy* boss);
	//�f�X�g���N�^
	~BossEnemyLeftShoulder() override;

};