#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyTorso : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "Torso";

public:
	//�R���X�g���N�^
	BossEnemyTorso(Scene* scene);
	//�f�X�g���N�^
	~BossEnemyTorso() override;

};