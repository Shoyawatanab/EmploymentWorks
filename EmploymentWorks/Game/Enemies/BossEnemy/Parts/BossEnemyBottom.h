#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyBottom : public BossEnemyParts
{
public:
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "Bottom";

public:
	//�R���X�g���N�^
	BossEnemyBottom(Scene* scene, BossEnemy* boss);
	//�f�X�g���N�^
	~BossEnemyBottom() override;

};