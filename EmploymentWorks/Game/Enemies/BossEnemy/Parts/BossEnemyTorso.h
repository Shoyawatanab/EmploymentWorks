#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyTorso : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "Torso";

public:
	//�R���X�g���N�^
	BossEnemyTorso(Scene* scene, BossEnemy* boss);
	//�f�X�g���N�^
	~BossEnemyTorso() override;

};