#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyPelvis : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "Pelvis";

public:
	//�R���X�g���N�^
	BossEnemyPelvis(Scene* scene);
	//�f�X�g���N�^
	~BossEnemyPelvis() override;

};