#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyLeftThigh : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "LeftThigh";

public:
	//�R���X�g���N�^
	BossEnemyLeftThigh(Scene* scene);
	//�f�X�g���N�^
	~BossEnemyLeftThigh() override;

};